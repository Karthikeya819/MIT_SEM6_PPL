#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[]){
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status st1;

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        for(int i = 1; i < size; i++)
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        
    }else{
        int number;
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st1);
        printf("Log: %d, Received %d from 0 \n", rank, number * 2);
    }

    MPI_Finalize();
}