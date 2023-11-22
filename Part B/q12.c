#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int size = 0; 

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4) {
        printf("Meant for 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int local = rank + 10;

    int sum = 0, mini = 0, maxi = 0, prod = 0;

    MPI_Allreduce(&local, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("[MPI Process %d]: Sum of all ranks is %d", rank, sum);

    MPI_Allreduce(&local, &maxi, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    printf("[MPI Process %d]: Max of all ranks is %d", rank, maxi); 

    MPI_Allreduce(&local, &mini, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    printf("[MPI Process %d]: Min of all ranks is %d", rank, mini);

    MPI_Allreduce(&local, &prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    printf("[MPI Process %d]: Prod of all ranks is %d", rank, prod);  

    MPI_Finalize();
}