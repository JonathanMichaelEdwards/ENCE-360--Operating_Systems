

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    int value = 0;

    int src = (world_rank + world_size - 1) % world_size;
    int dest = (world_rank + 1) % world_size;

    //Send off the first message around the ring
    if (world_rank == 0) {
        printf("%d: sending value %d to process %d\n", world_rank, value, dest);
        MPI_Send(&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }

    // Wait for a message
    MPI_Recv(&value, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%d: received value %d from process %d\n", world_rank, value, src);

    // If we aren't the first host then send the value on
    if (world_rank != 0) {
        value++;

        printf("%d: sending value %d to process %d\n", world_rank, value, dest);
        MPI_Send(&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }


    // Cleanup
    MPI_Finalize();
    return 0;
}