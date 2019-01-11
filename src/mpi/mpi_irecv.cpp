#include "mpi.h"
#include "ExaMPI.h"
#include "basic.h"
#include "interfaces/interface.h"


extern "C"
{

#pragma weak MPI_Irecv = PMPI_Irecv

	int PMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int dest, int tag,
	               MPI_Comm comm, MPI_Request *request)
	{
		int rc = exampi::BasicInterface::get_instance()->MPI_Irecv(buf, count, datatype,
		         dest, tag,
		         comm, request);
		return rc;
	}

}
