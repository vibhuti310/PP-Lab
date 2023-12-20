#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("Program for 2 processes only");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Status status;
    MPI_Request request;
    MPI_Comm-rank(MPI_COMM_WORLD, &rank);
    int number = 7;

    if(rank == 0)
    {
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Irecv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 0 received value %d", number);
    }

    if(rank == 1)
    {
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        MPI_Isend(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 1 received value %d", number);
    }

    MPI_Finalize();
}