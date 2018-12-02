#include "slave.h"

// Enum
enum neighbours {top, right, bottm, left};

int slave(MPI_Comm master_comm, MPI_Comm comm, int rank, double initial_time, int i, int *nmessage, FILE *fp) {
    
    // 1. initialization
    const char *Neighbours[] = {"top", "right", "bottom", "left"};  // mapping array to enum neighbours

    int adjacency_info[K][4], send_buff, recv_buff, j, tag = NON_EVENT_TAG;
    /*
     * adjacency[k][0]-[3] reps up, right, down, left Node respectively, mapped exactly with enum neighbour
     * send_buff: buffer that stores data(random number) to be send
     * recv_buff: buffer to ready to store the incoming data(random number)
     * tag: EVENT_TAG / NON_EVENT_TAG for sending event message from Nodes to base station
     */

    
    int event_send_info[6];
    /*
     event_send_info[0]: kth time reporting;
     event_send_info[1]: firing random number (i.e. 3 repeated number from neighbour Nodes)
     event_send_info[2]: top message
     event_send_info[3]: right message
     event_send_info[4]: bottom message
     event_send_info[5]: left message
     */
    MPI_Status status;
    MPI_Request request;
    
    // 2. generate random number
    send_buff = MIN + (rand() % (MAX-MIN+1));
    fprintf(fp, "-----In Node %d, generate a random number %d\n", rank, send_buff);
    
    
    
    // 3. sending messages
    /***********************************************/
    /***** Case 1: 2 adjacent neighbours Nodes *****/
    /***********************************************/
    
    /*** Case 1a: left-top corner ***/
    if (rank == 1) {
        
        //printf("Run process %d, which has %d adjacent neighbours.\n", rank, 2);
        
        
        // corner: 2 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 2;
        
    }
    
    /*** Case 1b: right-top corner ***/
    else if (rank == COL) {
        //printf("Run process %d, which has %d adjacent neighbours.\n", rank, 2);
        
        // corner: 2 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 2;
        
        
    }
    
    /*** Case 1c: right-bottom corner ***/
    else if (rank == COL*ROW) {
        // printf("Run process %d, which has %d adjacent neighbours.\n", rank, 2);
        
        // corner: 2 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        *nmessage = *nmessage + 2;
        
    }
    
    /*** Case 1d: left-bottom corner ***/
    else if (rank == COL*ROW-COL+1) {
        // printf("Run process %d, which has %d adjacent neighbours.\n", rank, 2);
        
        
        
        // corner: 2 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        *nmessage = *nmessage + 2;
        
        
        
    }
    
    /***********************************************/
    /***** Case 2: 3 adjacent neighbours Nodes *****/
    /***********************************************/
    
    /*** Case 2a: top edge (except for corners) ***/
    else if (rank > 1 && rank < COL){
        // printf("Run process %d, which has %d adjacent neighbours.\n", rank, 3);
        
        
        // edge: 3 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 3;
        
        
        
        
        int a = adjacency_info[i][1], b=adjacency_info[i][2], c =adjacency_info[i][3];
        if (a==b && b==c) {
            tag = EVENT_TAG;
            fprintf(fp, "Event triggered!!!!!!!!!!!!!!\n");
            
        }
        
    }
    
    /*** Case 2b: bottom edge (except for corners) ***/
    else if (rank > COL*ROW-COL+1 && rank < COL*ROW) {
        // printf("Run process %d, which has %d adjacent neighbours.\n", rank, 3);
        
        
        // edge: 3 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        *nmessage = *nmessage + 3;
        
        
        int a = adjacency_info[i][0], b=adjacency_info[i][1], c =adjacency_info[i][3];
        if (a==b && b==c){
            tag = EVENT_TAG;
            fprintf(fp, "Event triggered!!!!!!!!!!!!!!\n");
            
            
        }
    }
    
    /*** Case 2c: right edge (except for corners) ***/
    else if (rank % COL == 0) {
        // printf("Run process %d, which has %d adjacent neighbours.\n", rank, 3);
        
        
        // edge: 3 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 3;
        
        int a = adjacency_info[i][0], b=adjacency_info[i][2], c =adjacency_info[i][3];
        if (a==b && b==c){
            tag = EVENT_TAG;
            fprintf(fp, "Event triggered!!!!!!!!!!!!!!\n");
            
        }
    }
    
    /*** Case 2d: left edge (except for corners) ***/
    else if (rank % COL == 1) {
        //printf("Run process %d, which has %d adjacent neighbours.\n", rank, 3);
        
        // edge: 3 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 3;
        
        int a = adjacency_info[i][0], b=adjacency_info[i][1], c =adjacency_info[i][2];
        if (a==b && b==c){
            tag = EVENT_TAG;
            fprintf(fp, "Event triggered!!!!!!!!!!!!!!\n");
            
        }
    }
    
    
    /***********************************************/
    /***** Case 3: 4 adjacent neighbours Nodes *****/
    /***********************************************/
    
    /*** Case 3: internal Nodes ***/
    else {
        //printf("Run process %d, which has %d adjacent neighbours.\n", rank, 4);
        
        // inside: 4 adjacent neighbours
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-1, 0, &recv_buff, 1, MPI_INT, rank-1, 0, master_comm, &status); // left
        adjacency_info[i][3] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+1, 0, &recv_buff, 1, MPI_INT, rank+1, 0, master_comm, &status); // right
        adjacency_info[i][1] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank-COL, 0, &recv_buff, 1, MPI_INT, rank+COL, 0, master_comm, &status); // up
        adjacency_info[i][0] = recv_buff;
        
        MPI_Sendrecv(&send_buff, 1, MPI_INT, rank+COL, 0, &recv_buff, 1, MPI_INT, rank-COL, 0, master_comm, &status); // down
        adjacency_info[i][2] = recv_buff;
        
        *nmessage = *nmessage + 4;
        
        
        int a = adjacency_info[i][0], b=adjacency_info[i][1], c =adjacency_info[i][2], d = adjacency_info[i][3];
        
        if (((a==b) + (a==c) + (a==d) + (b==c) + (b==d) + (c==d)) >= 3){
            tag = EVENT_TAG;
            fprintf(fp, "Event triggered!!!!!!!!!!!!!!\n");
            
        }
    }
    
    
    
    // 4. write Node's information to log file
    for (j=top; j<=left; j++){
        if (adjacency_info[i][j] >= MIN && adjacency_info[i][j] <= MAX)
            fprintf(fp, "At %f seconds, Node %d messaged value %d (from %s)\n", MPI_Wtime() - initial_time, rank, adjacency_info[i][j], Neighbours[j]);
    }
    fprintf(fp, "\n");
    if (tag == EVENT_TAG){
        ++*nmessage;
        for (j=2; j<6; j++) {
            event_send_info[j] = adjacency_info[i][j-2];
        }
        event_send_info[0] = i + 1;
        if (event_send_info[2] == event_send_info[3])
            event_send_info[1] = event_send_info[2];
        else
            event_send_info[1] = event_send_info[4];
        if (tag == EVENT_TAG){
            MPI_Isend(event_send_info, 6, MPI_INT, 0, tag, master_comm, &request);
            MPI_Wait(&request, &status);
        }

    
    }
    
    
    return 0;
    
}
