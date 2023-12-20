#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int size;

    MPI_Comm_size(&size, MPI_COMM_WORLD);

    if(size != 2)
    {
        printf("This is meant for 2 processes only");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int sender = 0, receiver = 1;
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == sender)
    {
        int buffer = 1234;
        printf("Process %d sends value %d", rank, buffer);
        MPI_Send(&buffer, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
    }

    if(rank == receiver)
    {
        int value;
        MPI_Recv(&value, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
        printf("Process %d receives value %d", rank, value);
    }

    MPI_Finalize();
}