# Wireless-Sensor-Network
This project is a simulator of the communication between a base station and a fully distributed wireless sensor network.

## Description
The wireless sensor network comprises 20 nodes and a base station. These nodes are arranged in a 4 x 5 grid.

In this WSN Project, assuming that a set of 21 MPI processes represents the whole WSN and each MPI process maps a certain node in WSN. There’re totally 21 processes required to run the application.
The ‘rank 0’ MPI process represents the base station while ‘rank 1’ – ‘rank 20’ MPI process represents all network nodes.

There're typically two communication models in the mesh data structure.
### Communication Model 1
communication between Adjacent node →Adjacent node.
The program applies blocking(synchronous) communication between all adjacent neighbor Nodes. The following figure shows the simulation:

![WSN_model1](https://github.com/daniel2643/Wireless-Sensor-Network/blob/master/images/WSN_model1.png)

From this communication model, each node can only communicate with the adjacent nodes directly (i.e. top node, right node, bottom node, left node), but cannot chat with non-adjacent nodes (i.e. diagonal nodes).

The message passed between each adjacent node are random generated number in the range of 10, 11 or 12. There’re 3 categories of node which has been clarified in the program structure part.

For a specific node, for example, Node 1 generates an random number and sends the message(random number) to it right neighbor – Node 2 and its bottom neighbor – Node 6. Also, at the same time, Node 1 receives random number from Node 2 and Node 6 as well. For another instance, Node 7 generates an random number and sends the number to its neighbor – Node 2, Node 8, Node 12 and Node 6. Simultaneously, it receives random number from these four nodes.

The whole procedure would take 10 iterations (rounds). Between each round, there’s 1 second’s interval to make sure every processes can finish the task.

On Model 1, communication uses `MPI_Sendrecv()` which send and receive messages from adjacent neighbor.


### Communication Model 2
communication between Base station →Node.

The program applies non-blocking (asynchronous) communication between base station and each grid Node. The following figure demonstrated the communication between base station and grid nodes when event triggered.

![WSN_model2](https://github.com/daniel2643/Wireless-Sensor-Network/blob/master/images/WSN_model2.png)

In terms of Model 2, whenever there is an event firing in a node in the network, it reports a group of 6 messages, which are the iteration, the random number, top node random number, right node random number and left node random number, to the base station(Rank 0).

In figure 2, as an example, in a specific time interval round, Node 7(Rank 7) and Node 17(Rank 17) received at least 3 repeated random number from the neighbor nodes. When the event triggered, the two nodes non- blocking(asynchronous) send message packets to base station (Rank 0). In comparison, all other nodes that don’t receive at least 3 repeated random number won’t send messages to base station, which increases the efficiency of the wireless sensor network message passing system.

On Model 2, the communication is taken play by the following MPI operations:
- `MPI_Isend()` : non-blocking send message from nodes to base station
- `MPI_Irecv()`: non-blocking receive message by base station
- `MPI_Wait()`: wait for MPI request to complete
- `MPI_Test()`: test whether a request has been received
- `MPI_Cancel()`: cancels a communication request from node to base station
- `MPI_Request_free()`:frees a communication request object


## Compilation

1. open terminal

2. input commands
    `make clean`
    `make`
    `make run`
    
3. see results
    `cat result.txt`
    `cat message_stat.txt`













