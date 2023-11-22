#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4) {
        printf("Meant for 4 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int values[10], root_rank = 0;

    for(int i = 0; i < 10; i++)
        myvalues[i] = (rank + 1) * (i + 1);

    int max_val[10], min_val[10], sum_val[10], prod_val[10];

    MPI_Reduce(myvalues, max_val, 10, MPI_INT, MPI_MAX, root_rank, MPI_COMM_WORLD);
    MPI_Reduce(myvalues, min_val, 10, MPI_INT, MPI_MIN, root_rank, MPI_COMM_WORLD);
    MPI_Reduce(myvalues, prod_val, 10, MPI_INT, MPI_PROD, root_rank, MPI_COMM_WORLD);
    MPI_Reduce(myvalues, sum_val, 10, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);


    if(rank == root_rank) {
        printf("Reduction results : ");

        printf("MAX values :");
        for(int i = 0; i < 10; i++)
            printf("%d", max_val[i]);

        printf("MIN values :");
        for(int i = 0; i < 10; i++)
            printf("%d", min_val[i]);

        printf("PROD values :");
        for(int i = 0; i < 10; i++)
            printf("%d", prod_val[i]);

        printf("SUM values :");
        for(int i = 0; i < 10; i++)
            printf("%d", sum_val[i]);
    }

    MPI_Finalize();
}