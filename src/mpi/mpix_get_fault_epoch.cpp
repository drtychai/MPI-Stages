#include <ExaMPI.h>
#include <mpi.h>
#include "basic.h"
#include "interfaces/interface.h"

extern "C"
{
#pragma weak MPIX_Get_fault_epoch = PMPIX_Get_fault_epoch

	int PMPIX_Get_fault_epoch(int *out)
	{
		int rc = exampi::interface->MPIX_Get_fault_epoch(out);
		return rc;
	}

}

