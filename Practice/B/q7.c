#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("Only for 2 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int buf, root = 0;

    if(rank == root)
    {
        buf = 12345;
        printf("[MPI Process %d], broadcast sender - value %d", rank, buf);
    }

    MPI_Bcast(buf, 1, MPI_INT, root, MPI_COMM_WORLD);

    if(rank != root)
        printf("[MPI Process %d], receiver - value %d", rank, buf);

    MPI_Finalize();
}