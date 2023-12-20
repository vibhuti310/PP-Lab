#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2)
    {
        printf("Program meant for 2 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int number;

    if(rank == 0)
    {
        number = 0;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
       
    }

    if(rank == 1)
    {
        number = 1;
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Value %d received from process %d", number, rank - 1);
    }

    MPI_Finalize();
}