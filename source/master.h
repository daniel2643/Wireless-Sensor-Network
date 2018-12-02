#ifndef _master_h
#define _master_h

#include "mpi.h"
#include <stdio.h>
#include "slave.h"

#define TIMEOUT 0.01

int master(MPI_Comm master_comm, int size, double initial_time, int i, int *event);

#endif
