#include "master.h"
#include "slave.h"


int main(int argc, char **argv){
    // 1. initialization
    
    int rank, size, i, a = 0, b=0, *nmessage, total_nmessage = 0, *event;
    /*
     * nmessage: the total number of messages sended from one Node
     * total_message: the total number of messages throughout the network
     * event : the number of fired events
     */
    nmessage = &a;
    event = &b;

    
    
    double initial_time = MPI_Wtime();  /* start time of the system */
    
    
    FILE *fp, *mp;
    fp = fopen("nodes.log", "a");  /* filepath for log file */
    mp = fopen("message_stat.log", "a");  /* filepath for message statistics file */
    
    
    // 2. MPI initialization
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL) + rank);   /* random seed */
    
    if (size != COL*ROW + 1) {
        printf("Please run with %d processes.\n", COL*ROW+1);
        fflush(stdout);
        MPI_Abort( MPI_COMM_WORLD, 1 );
    }
    
    
    fprintf(fp, "*************************************************************************\n**************************    I'm Node  %d     **************************\n*************************************************************************\n", rank);
    

    
    // 3. Parallel Computing
    
    
    // split base station and network Nodes
    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, rank == 0 , 0, &new_comm);
    
    for (i=0; i<K; i++) {
        sleep(INTERVAL/1000);

        
        
        
        //////// Base Station /////////
        if (rank == 0){
            master(MPI_COMM_WORLD, size, initial_time, i, event);
        }
        ////////// Nodes ///////////
        else {
            slave(MPI_COMM_WORLD, new_comm, rank, initial_time, i, nmessage, fp);
        }

        
        
        
    }
    
    // 4. Number of messages report to message_stat file
    MPI_Reduce( nmessage, &total_nmessage, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );
    
    
    if (rank == 0)
        fprintf(mp, "Totally, there're %d messages throughout the network.\n", total_nmessage);
    else
        fprintf(mp, "On Node %d, there're %d messages throughout the network that send by this node.\n", rank, *nmessage);
    
    
    MPI_Comm_free(&new_comm);
    MPI_Finalize();
    fclose(fp);
    fclose(mp);
    return 0;
}


