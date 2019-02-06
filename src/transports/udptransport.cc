#include "transports/udptransport.h"
#include "universe.h"
#include "config.h"

namespace exampi
{

UDPTransport::UDPTransport() : Transport()
{
	// create
	socket_recv = socket(AF_INET, SOCK_DGRAM, 0);
	if(socket_recv == 0)
	{
		// TODO handle error
	}

	// setsockopt to reuse address
	//int opt = 1;
	//if(setsockopt(server_recv, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 

	// bind
	Universe& universe = Universe::get_root_universe();

	// garuntees no local collision
	int port = std::stoi(std::string(std::getenv("EXAMPI_UDP_TRANSPORT_BASE"))) + universe.rank;
	
	struct sockaddr_in address_local;
	address_local.sin_family = AF_INET;
	address_local.sin_addr.s_addr = INADDR_ANY;
	address_local.sin_port = htons(port);

	if(bind(socket_recv, (sockaddr*)&address_local, sizeof(address_local)) < 0)
	{
		// TODO handle error
	}

	// prepare msg header
	hdr.msg_name = NULL;
	hdr.msg_namelen = 0;

	hdr.msg_control = NULL;
	hdr.msg_controllen = 0;
	hdr.msg_flags = 0;

	// cache remote addresses
	Config& config = Config::get_instance();

	for(long int rank = 0; rank < universe.world_size; ++rank)
	{
		std::string descriptor = config[std::to_string(rank)];
		size_t delimiter = descriptor.find_first_of(":");
		std::string ip = descriptor.substr(0, delimiter);
		int port = std::stoi(descriptor.substr(delimiter+1));

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(ip.c_str()); 
		addr.sin_port = htons(port);

		cache.insert({rank, addr});
	}
}

UDPTransport::~UDPTransport()
{
	close(socket_recv);
}

bool UDPTransport::peek(ProtocolMessage_uptr &message)
{
	// early exit test
	char test;
	ssize_t size = recv(socket_recv, &test, sizeof(test), MSG_PEEK | MSG_DONTWAIT);
	if(size <= 0)
		return false;

	std::lock_guard<std::mutex> lock(guard);

	// check again, that the data has not been taken by another thread
	size = recv(socket_recv, &test, sizeof(test), MSG_PEEK | MSG_DONTWAIT);
	if(size <= 0)
		return false;

	ProtocolMessage_uptr msg = allocate_protocol_message();

	// fill iov
	iovec msg_iov;
	msg_iov.iov_base = msg.get();
	msg_iov.iov_len = sizeof(ProtocolMessage);

	hdr.msg_iov = &msg_iov;
	hdr.msg_iovlen = 1;

	// clear source
	hdr.msg_name = NULL;
	hdr.msg_namelen = 0;

	int err = recvmsg(socket_recv, &hdr, 0);
	// TODO handle error

	message = std::move(msg);

	return true;
}

int UDPTransport::reliable_send(ProtocolMessage_uptr message)
{
	std::lock_guard<std::mutex> lock(guard);

	// fill iov
	iovec msg_iov;
	msg_iov.iov_base = message.get();
	msg_iov.iov_len = sizeof(ProtocolMessage);
	
	hdr.msg_iov = &msg_iov;
	hdr.msg_iovlen = 1;

	// fill destination
	sockaddr_in &addr = cache[message->envelope.destination];
	hdr.msg_name = &addr;
	hdr.msg_namelen = sizeof(sockaddr_in);

	int err = sendmsg(socket_recv, &hdr, 0);
	// TODO handle error
	
	return MPI_SUCCESS;
}

}
