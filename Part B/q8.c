#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("To be run with 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int root_rank = 0, my_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int my_value = my_rank * 100;

    printf("Process %d, my value = %d", my_rank, my_value);

    if(my_rank == root_rank)
    {
        int buf[4];
        MPI_Gather(&my_value, 1, MPI_INT, buf, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Process %d collected values: %d %d %d %d", my_rank, buf[0], buf[1], buf[2], buf[3]);
    }

    if(my_rank != root_rank)
    {
        MPI_Gather(&my_value, 1, MPI_INT, NULL, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}