#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int msg_size = 64, rank, size;
    char *buf;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2)
    {
        printf("Not for 2 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Status status;
    double start, end;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Process %d starts...", rank);

    while(msg_size < 100000000)
    {
        msg_size *= 2;
        buf = (char *) malloc(msg_size * sizeof(char));

        start = MPI_Wtime();
        if(rank == 0)
            MPI_Sendrecv(buf, msg_size, MPI_BYTE, 1, tag, buf, msg_size, MPI_BYTE, 1, tag, MPI_COMM_WORLD, &status);
        else if(rank == 1)
            MPI_Sendrecv(buf, msg_size, MPI_BYTE, 0, tag, buf, msg_size, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &status);
        end = MPI_Wtime();

        double time = end - start;
        double bandwidth = (msg_size/(1024 * 1024)) / time;

        printf("Message size: %d, Time taken: %.6f sec, Bandwidth: %.2f MB/s");
        fflush(stdout);

        free(buf);
    }

    MPI_Finalize();
}