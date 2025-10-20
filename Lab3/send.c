#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size); // total processes

    char message[100];

    if (size < 2) {
        if (rank == 0) {
            printf("This program needs at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    // if (rank == 0) { 
    //     strcpy(message, "Hello from Process 0");
    //     MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    //     printf("Process 0 send message: %s\n", message);
    // } else if (rank == 1) {
    //     MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     printf("Process 1 received message: %s\n", message);
    // } 
    




    // else if (rank == 2) {
    //     strcpy(message, "Hello from Process 2");
    //     MPI_Send(message, strlen(message) + 1, MPI_CHAR, 3, 0, MPI_COMM_WORLD);
    //     printf("Process 2 send message: %s\n", message);
    // }else if (rank == 3) {
    //     MPI_Recv(message, 100, MPI_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     printf("Process 3 received message: %s\n", message);
    //  }
    
    else if (rank == 4) {
        strcpy(message, "Hello from Process 4");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 5, 0, MPI_COMM_WORLD);
        printf("Process 4 send message: %s\n", message);
     }else if (rank == 5) {
        MPI_Recv(message, 100, MPI_CHAR, 4, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 5 Receive message: %s\n", message);
     }

    MPI_Finalize();
    return 0;
}
