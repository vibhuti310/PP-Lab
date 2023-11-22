#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 4)
    {
        printf("Only for 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int root_rank = 0, value;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root_rank)
    {
        int buf[4] = {100, 120, 130, 140};
        printf("Values to scatter from: %d %d %d %d", buf[0], buf[1], buf[2], buf[3]);
        MPI_Scatter(buf, 1, MPI_INT, &value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    else
    {
        MPI_Scatter(NULL, 1, MPI_INT, &value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    printf("Process %d received value = %d", rank, value);
    MPI_Finalize();
}