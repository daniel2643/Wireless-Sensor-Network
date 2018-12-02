# Wireless-Sensor-Network
This project is a simulator of the communication between a base station and a fully distributed wireless sensor network.

## Description
The wireless sensor network comprises 20 nodes and a base station. These nodes are arranged in a 4 x 5 grid.

In this WSN Project, assuming that a set of 21 MPI processes represents the whole WSN and each MPI process maps a certain node in WSN. There’re totally 21 processes required to run the application.
The ‘rank 0’ MPI process represents the base station while ‘rank 1’ – ‘rank 20’ MPI process represents all network nodes.

