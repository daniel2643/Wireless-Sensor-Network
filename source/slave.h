#ifndef _slave_h
#define _slave_h


#include "mpi.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define COL 5                       /* the number of columns in the network */
#define ROW 4                       /* the number of rows in the network */
#define K 10                        /* times of iteration(detection) */
#define INTERVAL 1000               /* time delays in each iteration(detection) */
#define MAX 12                      /* max random number */
#define MIN 10                      /* min random number */

// MPI_TAGs
#define EVENT_TAG 0
#define NON_EVENT_TAG 1

int slave(MPI_Comm master_comm, MPI_Comm comm, int rank, double initial_time, int i, int *nmessage, FILE *fp);


#endif
