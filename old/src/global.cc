#include <global.h>

#include "engines/blockingprogress.h"
#include "transports/transport.h"
#include "checkpoints/checkpoint.h"

namespace exampi
{

std::unordered_map<MPI_Datatype, exampi::Datatype> datatypes =
{

	{ MPI_BYTE, Datatype(MPI_BYTE,           sizeof(unsigned char),  true,  true, true)},
	{ MPI_CHAR, Datatype(MPI_CHAR,           sizeof(char),           true,  true, true)},
#if 0
	{ MPI_WCHAR, Datatype(MPI_WCHAR,          sizeof(wchar_t),        true,  true, true)},
#endif
	{ MPI_UNSIGNED_CHAR,  Datatype(MPI_UNSIGNED_CHAR,  sizeof(unsigned char),  true,  true, true)},
	{ MPI_SHORT,          Datatype(MPI_SHORT,          sizeof(short),          true,  true, true)},
	{ MPI_UNSIGNED_SHORT, Datatype(MPI_UNSIGNED_SHORT, sizeof(unsigned short), true,  true, true)},
	{ MPI_INT,            Datatype(MPI_INT,            sizeof(int),            true,  true, true)},
	{ MPI_UNSIGNED_INT,   Datatype(MPI_UNSIGNED_INT,   sizeof(unsigned int),   true,  true, true)},
	{ MPI_LONG,           Datatype(MPI_LONG,           sizeof(long),           true,  true, true)},
	{ MPI_UNSIGNED_LONG,  Datatype(MPI_UNSIGNED_LONG,  sizeof(unsigned long),  true,  true, true)},
	{ MPI_FLOAT,          Datatype(MPI_FLOAT,          sizeof(float),          false, true, true)},
	{ MPI_DOUBLE,         Datatype(MPI_DOUBLE,         sizeof(double),         false, true, true)},
	{ MPI_LONG_LONG_INT,  Datatype(MPI_LONG_LONG_INT,  sizeof(long long int),  false, true, true)},
	{ MPI_LONG_LONG,      Datatype(MPI_LONG_LONG,      sizeof(long long),      false, true, true)},
	{ MPI_FLOAT_INT,		Datatype(MPI_FLOAT_INT,		 sizeof(float_int_type), false, false, false)},
	{ MPI_LONG_INT,		Datatype(MPI_LONG_INT,		 sizeof(long_int_type),  false, false, false)},
	{ MPI_DOUBLE_INT,		Datatype(MPI_DOUBLE_INT,	 sizeof(double_int_type),false, false, false)},
	{ MPI_2INT,		    Datatype(MPI_2INT,	 		 sizeof(int_int_type),   false, false, false)},
#if 0
	{ MPI_LONG_DOUBLE, Datatype(MPI_LONG_DOUBLE,    sizeof(long double),    false, true, true)},
#endif
};

} // exampi