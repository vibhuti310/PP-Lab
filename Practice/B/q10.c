#include <stdio.h>
#include <mpi.h>

#define arr_size 20

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("4 processes only");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int buf[4] = {100, 110, 130, 140};
    int recv;

    MPI_Scatter(buf, 1, MPI_INT, recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d gathered %d value", rank, recv);

    recv += 10;
    int gathered_data[4];

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&recv, 1, MPI_INT, gathered_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Gathered values:");
        for(int i = 0; i < size; i++)
        {
            printf("%d", gathered_data[i]);
        }
    }

    MPI_Finalize();
}