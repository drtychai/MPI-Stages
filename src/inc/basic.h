#include <ExaMPI.h>
#include <UDPSocket.h>
#include <config.h>
#include <fstream>
#include <iostream>

namespace exampi
{

const std::string runtimeConfig("mpihosts.stdin.tmp");

class BasicTransport : public ITransport
{
  private:
    std::string address;
    uint16_t port;
    Config *config;
  public:
    BasicTransport(Config *c) : config(c) {};
        
    virtual void send(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
      std::cout << "In BasicTransport.send(...,rank="<<dest<<",...)" << std::endl;
      std::string rank = std::to_string(dest);
      std::string destip = (*config)[rank];
      port = 8080;
      try {
        UDPSocket sock;
        sock.send(buf, count, destip.c_str(), port);
      } catch (std::exception &ex) {
          std::cerr << ex.what() << std::endl;
          exit(1);  
      }
    }
    
    virtual int recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
      //TODO: figure out port from source
      port = 8080;
      try {
         UDPSocket sock(port);
         std::string sourceAddress;
         uint16_t sourcePort;
         int recvDataSize;
            recvDataSize = sock.recv(buf, count, sourceAddress, sourcePort);
            std::cout << "Received packet from " << sourceAddress << " : " << sourcePort << " : " << buf << std::endl;
      } catch (std::exception &ex) {
          std::cerr << ex.what() << std::endl;
          exit(1);
      }
      return 0;
    }

};
class BasicProgress : public IProgress
{
  private:
    Config *config;
    BasicTransport btransport;

  public:
    BasicProgress(Config *c) : config(c), btransport(config) {};
        
    virtual int send_data(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
      btransport.send(buf, count, datatype, dest, tag, comm);
      return 0;
    }
    virtual int recv_data(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
      btransport.recv(buf, count, datatype, source, tag, comm, status);
      return 0;
    }

};

class BasicInterface : public IInterface
{
  private:
    int rank;  // TODO: Don't keep this here, hand off to progress
    int ranks;
    std::vector<std::string> hosts;
    Config config;
    BasicProgress bprogress;

  public:
    static BasicInterface *global;

    BasicInterface() : rank(0), config(), bprogress(&config) {};
    virtual int MPI_Init(int *argc, char ***argv)
    {
// argv is char**  -- strings are char*
// so it's a ptr to str
// argv ref is char***
// ptr to ptr to str

      // first param is config file, second is rank
      std::cout << "Loading config from " << **argv << std::endl;
      config.Load(**argv);
      (*argv)++;
      (*argc)--;
      std::cout << "Taking rank to be arg " << **argv << std::endl;
      rank = atoi(**argv);
      (*argv)++;
      (*argc)--;
      return 0;
    }
    virtual int MPI_Finalize() { return 0; }

    virtual int MPI_Send(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
    	bprogress.send_data(buf, count, datatype, dest, tag, comm);
    	return 0;
    }

    virtual int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
    	bprogress.recv_data(buf, count, datatype, source, tag, comm, status);
    	return 0;
    }

    virtual int MPI_Comm_rank(MPI_Comm comm, int *r)
    {
      *r = rank;
      return 0;
    }

    virtual int MPI_Comm_size(MPI_Comm comm, int *r)
    {
      *r = std::stoi(config["size"]);
      return 0;
    }
};


} // namespace exampi