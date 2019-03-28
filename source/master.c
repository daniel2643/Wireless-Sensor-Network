#include "master.h"

int master(MPI_Comm master_comm, int size, double initial_time, int i, int *event){

    int j, event_recv_info[6], flag;
    /*
    event_recv_info[0]: kth time reporting;
    event_recv_info[1]: firing random number (i.e. 3 repeated number from neighbour Nodes)
    event_recv_info[2]: top message
    event_recv_info[3]: right message
    event_recv_info[4]: bottom message
    event_recv_info[5]: left message
    */
    
    double a_time;   /*  test start time  */
    
    FILE *rp;
    rp = fopen("base_station.log", "a");  /* filepath for result file */
    
    MPI_Status status;
    MPI_Request request;
    printf("\nRound %d: Monitoring Base-Station.\n", i+1);
    //sleep(1);
    for (j=1; j<size; j++){
        // if wait for sometime for one node and cannot receive, then just stop
        MPI_Irecv(event_recv_info, 6, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, master_comm, &request);
        a_time = MPI_Wtime();
        MPI_Test(&request, &flag, &status);
        while (!flag && MPI_Wtime()-a_time < TIMEOUT){
            MPI_Test(&request, &flag, &status);
        }
        // Base station cannot receive the event firing message from Node j
        if (!flag) {
            MPI_Cancel(&request);
            MPI_Request_free(&request);
        }
        // Base station received the event firing message from Node j
        else {
            ++*event;
            printf("Event happened in Node %d\n", status.MPI_SOURCE);
            fprintf(rp, "At %f seconds, event detected from reference Node %d, the firing number is %d ----Total Events: %d\n", MPI_Wtime()-initial_time, status.MPI_SOURCE, event_recv_info[1], *event);
            fprintf(rp, "The adjacent neighbours are: ");
            
            // report the adjacent neighbours which fire the event
            if (event_recv_info[2] >= MIN && event_recv_info[2] <= MAX)
                fprintf(rp, "Node %d (top)  ", status.MPI_SOURCE-COL);
            
            if (event_recv_info[3] >= MIN && event_recv_info[3] <= MAX)
                fprintf(rp, "Node %d (right)  ", status.MPI_SOURCE+1);
            
            if (event_recv_info[4] >= MIN && event_recv_info[4] <= MAX)
                fprintf(rp, "Node %d (bottom)  ", status.MPI_SOURCE+COL);
            
            if (event_recv_info[5] >= MIN && event_recv_info[5] <= MAX)
                fprintf(rp, "Node %d (left)  ", status.MPI_SOURCE-1);
            
            fprintf(rp, "\n\n");
            
        }
    }
    
    fclose(rp);
    return 0;
}
