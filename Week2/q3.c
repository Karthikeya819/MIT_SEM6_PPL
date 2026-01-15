#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){

    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status st1;

    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
    int *buffer = (int*)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        int data[] = {1, 2, 3, 4};
        for(int i = 1; i < size; i++)
            MPI_Bsend(&data[(i-1)%4], 1, MPI_INT, i, 0, MPI_COMM_WORLD);   
    }
    else{
        int num;
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st1);
        num = (rank%2 == 0)?num*num: num*num*num;
        printf("Log %d, Processed val: %d \n", rank, num);
    }

    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    MPI_Finalize();

    return 0;
}