#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = rank;
    int max_val, min_val, sum, prod;

    MPI_Reduce(&data, &max_val, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&data, &min_val, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Reduce(&data, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&data, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Max value: %d", max_val);
        printf("Min value: %d", min_val);
        printf("Sum of values: %d", sum);
        printf("Product of values: %d", prod);
    }

    MPI_Finalize();
}