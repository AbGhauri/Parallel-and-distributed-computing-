#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);                  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    // Get this process' rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Get total number of processes

    if (rank == 0) {
        data = 42;   // Root process sets the data
        printf("Process %d broadcasting data = %d\n", rank, data);
    }

    // Broadcast 'data' from process 0 to all processes
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process now has the same value of 'data'
    printf("Process %d received data = %d\n", rank, data);

    // Same like BCast
    // if (rank == 0) {
    // for (int i = 1; i < size; i++) {
    //     MPI_Send(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    // }
    // } else {
    // MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // }

    MPI_Finalize();   // Clean up MPI
    return 0;
}
