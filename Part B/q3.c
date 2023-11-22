#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int size, rank, tag = 100, msg_size = 64;
    char *buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2)
    {
        printf("Must run for two processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    fflush(stdout);
    while(msg_size < 100000000)
    {
        msg_size *= 2;
        buf = (char *)malloc(msg_size * sizeof(char));

        if(rank == 0)
        {
            MPI_Send(buf, msg_size, MPI_BYTE, rank + 1, tag, MPI_COMM_WORLD);
            printf("Message of length %d to %d", msg_size, rank + 1);
            fflush(stdout);
            MPI_Recv(buf, msg_size, MPI_BYTE, rank + 1, tag, MPI_COMM_WORLD, &status);
        }

        if(rank == 1)
        {
            MPI_Recv(buf, msg_size, MPI_BYTE, rank - 1, tag, MPI_COMM_WORLD, &status);
            printf("Message of length %d to %d", msg_size, rank - 1);
            fflush(stdout);
            MPI_Send(buf, msg_size, MPI_BYTE, rank - 1, tag, MPI_COMM_WORLD);
        }

        free(buf);
    }

    MPI_Finalize();
}