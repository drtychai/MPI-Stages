#ifndef __EXAMPI_SIMPLE_MATCHER_H
#define __EXAMPI_SIMPLE_MATCHER_H

#include <list>
#include <queue>
#include <mutex>

#include "abstract/matcher.h"
#include "protocol.h"

namespace exampi
{

class SimpleMatcher final: public Matcher
{
private:
	std::mutex guard;

	std::queue<ProtocolMessage_uptr> unexpected_message_queue;
	std::list<Request_ptr> posted_receive_queue;

	unsigned int new_receives;
	
public:
	SimpleMatcher();

	void post_request(Request_ptr request);

	bool match(ProtocolMessage_uptr message, Match &match);
	bool progress(Match &match);
	bool has_work();
};

}

#endif 
