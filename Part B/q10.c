#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 20

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(size != 4)
    {
        printf("Designed for 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE;
    }

    int arr[ARRAY_SIZE];
    int localArr[ARRAY_SIZE/size];
    int localsum = 0;
    int sum[size];

    if(rank == 0)
    {
        for(int i = 0; i < ARRAY_SIZE; i++)
            arr[i] = i + 1;
    }

    MPI_Scatter(arr, ARRAY_SIZE/size, MPI_INT, localArr, ARRAY_SIZE/size, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < ARRAY_SIZE/size; i++)
    {
        localsum += localArr[i];
    }

    MPI_Gather(&localsum, 1, MPI_INT, sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("Original Array: ");
        for(int i = 0; i < ARRAY_SIZE; i++) 
            printf("%d", arr[i]);

        for(int i = 0; i < size; i++)
            printf("Sum from process %d: %d", rank, sum[i]);
    }

    MPI_Finalize();
}