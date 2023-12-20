#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size != 4)
    {
        printf("For 4 processes only");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMMM_WORLD, &rank);
    int root = 0, value;
    int buf[4] = {100, 110, 120, 130};

    if(root == rank)
    {
        printf("Scattering values : %d %d %d %d", buf[0], buf[1], buf[2], buf[3]);
        MPI_Scatter(buf, 1, MPI_INT, &value, 1, MPI_INT, root, MPI_COMM_WORLD);
    }

    else
    {
        MPI_Scatter(NULL, 1, MPI_INT, &value, 1, MPI_INT, rank, MPI_COMM_WORLD);
    }
}