#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("To be run with 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int my_value = 100 * rank;
    int root_rank = 0;

    if(rank == root_rank)
    {
        int buf[4];
        MPI_Gather(&my_value, 1, MPI_INT, buf, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Process %d - Values gathered: %d %d %d %d", rank, buf[0], buf[1], buf[2], buf[3]);
    }

    if(rank != root_rank)
    {
        MPI_Gather(&my_value, 1, MPI_INT, NULL, 1, MPI_INT, rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}