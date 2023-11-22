#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2)
    {
        printf("Must run for two processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number = 7;
    MPI_Status status;
    MPI_Request request;

    if(rank == 0)
    {
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Irecv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 0 received %d from process 1", number);
    }

    if(rank == 1)
    {
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        MPI_Isend(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process 1 sent %d to process 0", number);
    }

    MPI_Finalize();
}