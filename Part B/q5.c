#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank, msg_size = 64, tag = 100;
    char *buf;

    MPI_Init(*argc, *argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2)
    {
        printf("Must run for two processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Process %d has started...", rank);
    double start_time, end_time;

    MPI_Status status;

    while(msg_size < 100000000)
    {
        buf = (char*)malloc(msg_size * sizeof(char));

        start_time = MPI_Wtime();
        if(rank == 0)
            MPI_Sendrecv(buf, msg_size, MPI_BYTE, 1, tag, buf, msg_size, MPI_BYTE, 1, tag, MPI_COMM_WORLD, &status);
        else if(rank == 1)
            MPI_Sendrecv(buf, msg_size, MPI_BYTE, 0, tag, buf, msg_size, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &status);

        end_time = MPI_Wtime();
        double time_taken = end_time - start_time;
        double bandwidth = (msg_size/(1024 * 1024)) / time_taken;

        printf("Message size: %d bytes, Time taken: %.6f seconds, Bandwidth: %.2f MB/s", msg_size, time_taken, bandwidth);
        fflush(stdout);

        free(buf);
        msg_size *= 2;
    }

    MPI_Finalize();
}