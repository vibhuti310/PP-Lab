#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(*argc, *argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("Runs with 2 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Phase 1, Process %d of %d", rank, size);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Phase 2, Process %d of %d", rank, size);
    MPI_Finalize();
}