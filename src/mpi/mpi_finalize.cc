#include "mpi.h"

#include "interfaces/interface.h"

extern "C"
{
	#pragma weak MPI_Finalize = PMPI_Finalize

	int PMPI_Finalize(void)
	{
		exampi::Universe &universe = exampi::Universe::get_root_universe();

		return universe.interface->MPI_Finalize();
	}
}

