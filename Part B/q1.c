#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 2) 
    {
        printf("Application should run with 2 processes");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int Sender = 0, Reciever = 1;

    if(my_rank == Sender)
    {
        int buffer = 1234;
        printf("MPI Process %d sends value %d\n", my_rank, buffer);
        MPI_Send(&buffer, 1, MPI_INT, Reciever, 0, MPI_COMM_WORLD);
    }

    else if(my_rank == Reciever)
    {
        int recieved;
        MPI_Recv(&recieved, 1, MPI_INT, Sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("MPI process %d receives %d value", my_rank, recieved);
    }

    MPI_Finalize();
    return 0;
}