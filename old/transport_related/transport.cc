#include "transports/transport.h"
#include "transports/udp.h"

namespace exampi
{

//BasicTransport::BasicTransport()
//{
//	debugpp("library begins here");
//
//	// todo this is a dirty hack to "fix" the problem of rank not being correctly initialized yet
//	// that is due to conversion from global to singletons
//	if(exampi::rank == -1)
//	{
//		exampi::rank = std::stoi(std::string(std::getenv("EXAMPI_RANK")));
//	}
//
//	debugpp("transport base_port: " << std::string(
//	            std::getenv("EXAMPI_UDP_TRANSPORT_BASE")));
//	base_port = std::stoi(std::string(std::getenv("EXAMPI_UDP_TRANSPORT_BASE")));
//	port = base_port + exampi::rank;
//
//	debugpp("transport ports: " << base_port << " " << port << " for rank " <<
//	        exampi::rank);
//}
//
//void BasicTransport::init()
//{
//	// add all endpoints
//	debugpp("adding endpoints");
//
//	Config &config = Config::get_instance();
//
//	for(long int rank = 0; rank < exampi::worldSize; ++rank)
//	{
//		std::string descriptor = config[std::to_string(rank)];
//
//		size_t delimiter = descriptor.find_first_of(":");
//		std::string ip = descriptor.substr(0, delimiter);
//		std::string port = descriptor.substr(delimiter+1);
//
//		Address address(ip, std::stoi(port));
//		endpoints[rank] = address;
//		debugpp("added address for rank " << rank << " as " << ip << " " << port);
//	}
//
//	// bind port
//	debugpp("binding udp port " << this->port);
//	recvSocket.bindPort(this->port);
//}
//
//void BasicTransport::init(std::istream &t)
//{
//	init();
//}
//
//void BasicTransport::finalize()
//{
//	recvSocket.destroy();
//}
//
//std::future<int> BasicTransport::send(std::vector<struct iovec> &iov, int dest,
//                                      MPI_Comm comm)
//{
//	debugpp("basic::Transport::send(..., " << dest << ", " << comm);
//
//	Socket s;
//
//	Message msg(iov);
//
//	//debugpp("basic::Transport::send: endpoints" << endpoints[dest]);
//	msg.send(s, endpoints[dest]);
//
//	return std::promise<int>().get_future();
//}
//
//std::future<int> BasicTransport::receive(std::vector<struct iovec> &iov,
//        MPI_Comm comm,
//        ssize_t *count)
//{
//	debugpp("basic::Transport::receive(...)");
//	debugpp("\tiov says size is " << iov.size());
//
//	Message msg(iov);
//
//	debugpp("basic::Transport::receive, constructed msg, calling msg.receive");
//	//msg.receive(recvSocket, tcpSock); /*For TCP transport*/
//
//	*count = msg.receive(recvSocket);
//
//	debugpp("basic::Transport::receive returning");
//
//	return std::promise<int>().get_future();
//}
//
//int BasicTransport::cleanUp(MPI_Comm comm)
//{
//	//std::cout << debug() << "basic::Transport::receive(...)" << std::endl;
//	char buffer[2];
//	struct sockaddr_storage src_addr;
//
//	struct iovec iov[1];
//	iov[0].iov_base=buffer;
//	iov[0].iov_len=sizeof(buffer);
//
//	struct msghdr message;
//	message.msg_name=&src_addr;
//	message.msg_namelen=sizeof(src_addr);
//	message.msg_iov=iov;
//	message.msg_iovlen=1;
//	message.msg_control=0;
//	message.msg_controllen=0;
//
//
//	//std::cout << debug() <<
//	//          "basic::Transport::receive, constructed msg, calling msg.receive" << std::endl;
//
//	//std::cout << debug() << "basic::Transport::udp::recv\n";
//
//	recvmsg(recvSocket.getFd(), &message, MSG_WAITALL);
//	//std::cout << debug() << "basic::Transport::udp::recv exiting\n";
//	//std::cout << debug() << "basic::Transport::receive returning" << std::endl;
//	return 0;
//}
//
//int BasicTransport::peek(std::vector<struct iovec> &iov, MPI_Comm comm)
//{
//	debugpp("peek: msg.peek()");
//
//	Message msg(iov);
//	//msg.peek(recvSocket, tcpSock); /*For TCP transport*/
//	msg.peek(recvSocket);
//
//	return 0;
//}
//
///*std::vector<std::string> split(std::vector<std::string> vec, std::string line) {
//	vec.clear();
//	std::size_t delim = line.find_first_of("|");
//	std::string key = line.substr(0, delim);
//	vec.push_back(key);
//	std::string val = line.substr(delim+1);
//	vec.push_back(val);
//	return vec;
//}*/
//
//int BasicTransport::save(std::ostream &t)
//{
//	// save endpoints
//	int epsz = endpoints.size();
//	//std::cout << "size: " << epsz << "\n";
//	t.write(reinterpret_cast<char *>(&epsz), sizeof(int));
//	for(auto i : endpoints)
//	{
//		auto key = i.first;
//		auto val = i.second;
//		t.write(reinterpret_cast<char *>(&key), sizeof(key));
//		t.write(reinterpret_cast<char *>(&val), sizeof(val));
//	}
//	return 0;
//}
//
//int BasicTransport::load(std::istream &t)
//{
//	init();
//	// load endpoints
//	int epsz;
//	int rank;
//	Address addr;
//	t.read(reinterpret_cast<char *>(&epsz), sizeof(int));
//	//std::cout << "size: " << epsz << "\n";
//	while(epsz)
//	{
//		t.read(reinterpret_cast<char *>(&rank), sizeof(rank));
//		t.read(reinterpret_cast<char *>(&addr), sizeof(addr));
//		endpoints[rank] = addr;
//		epsz--;
//	}
//	return 0;
//}


}
