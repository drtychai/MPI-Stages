#include <ExaMPI.h>
#include <iostream>
#include <string>

namespace exampi
{

class BasicProgress : public IProgress
{
  private:
    BasicTransport btransport;
    std::vector<std::string> hosts;

  public:
    BasicProgress() : btransport() {};
        
    virtual int send_data(const void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
      btransport.send(buf, count, datatype, dest, tag, comm);
      return 0;
    }
    virtual int recv_data(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
      btransport.recv(buf, count, datatype, source, tag, comm, &status);
      return 0;
    }

    void SetHosts(std::vector<std::string> h) 
    {
      btransport.SetHosts(h);
    }
};

}
