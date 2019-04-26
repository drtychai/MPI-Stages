#ifndef __EXAMPI_ABSTRACT_PROGRESS_H
#define __EXAMPI_ABSTRACT_PROGRESS_H

#include <mpi.h>

#include "request.h"
#include "abstract/stages.h"

namespace exampi
{

class Progress: virtual public Stages
{
public:
	virtual ~Progress() {}

	// handle user request object
	virtual void post_request(Request *request) = 0;
};

} // ::exampi

#endif // __EXAMPI_PROGRESS_H
