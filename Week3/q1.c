#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int fact_num(int n){
    if(n <= 1) return 1;
    return n * fact_num(n-1);
}

int main(int argc, char *argv[]){
    int size, rank, *arr, recvBuf;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        arr = (int*) calloc(size, sizeof(int));
        for(int i = 0; i< size; i++)scanf("%d", arr+i);
    }

    MPI_Scatter(arr, 1, MPI_INT, &recvBuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    recvBuf = fact_num(recvBuf);

    MPI_Gather(&recvBuf, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int sum = 0;
        for(int i =0; i< size; i++)sum += arr[i];
        printf("The Sum of Response received from each process is %d \n", sum);
    }

    MPI_Finalize();
    return 0;
}