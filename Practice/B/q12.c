#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = rank;
    int max_val, min_val, sum, prod;

    MPI_Allreduce(&data, &max_val, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&data, &min_val, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&data, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&data, &prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

    printf("Process %d - Max %d - Min %d - Sum %d - Prod %d", rank, max_val, min_val, sum, prod);
    MPI_Finalize();
}