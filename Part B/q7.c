#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int broadcast_root = 0, buf;

    if(rank == broadcast_root)
    {
        buf = 12345;
        printf("[MPI Process %d] I am broadcast root, and send value %d", rank, buf);
    }

    MPI_Bcast(&buf, 1, MPI_INT, broadcast_root, MPI_COMM_WORLD);
    if(rank != broadcast_root)
    {
        printf("[MPI Process %d] I am a broadcast receiver, and obtained value %d", rank, buf);
    }

    MPI_Finalize();

}