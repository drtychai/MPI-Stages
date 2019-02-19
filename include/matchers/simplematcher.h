#ifndef __EXAMPI_SIMPLE_MATCHER_H
#define __EXAMPI_SIMPLE_MATCHER_H

#include <list>
#include <mutex>

#include "abstract/matcher.h"

namespace exampi
{

class SimpleMatcher final: public Matcher
{
private:
	std::mutex guard;

	std::list<Request_ptr> posted_request_queue;
	//std::list<ProtocolMessage_uptr> received_message_queue;
	std::list<Header *> received_header_queue;

	bool change;

public:
	SimpleMatcher();

	void post_request(Request_ptr request);

	//void post_message(const ProtocolMessage_uptr message);
	void post_header(Header *header);

	bool progress(Match &match);

	//std::tuple<bool, Request_ptr, ProtocolMessage_uptr> progress();

	void halt();
};

}

#endif
