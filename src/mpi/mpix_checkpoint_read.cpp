#include <ExaMPI.h>
#include <mpi.h>
#include "basic.h"
#include "basic/interface.h"

extern "C"
{
#pragma weak MPIX_Checkpoint_read = PMPIX_Checkpoint_read

int PMPIX_Checkpoint_read() {
  int rc = exampi::global::interface->MPIX_Checkpoint_read();
  return rc;
}

}