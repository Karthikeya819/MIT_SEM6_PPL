#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank, *arr, m, *recvBuf;
    float *recvArr;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        scanf("%d", &m);
        arr = (int*)calloc(m*size, sizeof(int));
        for(int i = 0; i < m*size; i++)scanf("%d", arr + i);
        recvArr = (float*) calloc(size, sizeof(float));
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    recvBuf = (int*) calloc(m, sizeof(int));
    MPI_Scatter(arr, m, MPI_INT, recvBuf, m, MPI_INT, 0, MPI_COMM_WORLD);
    float sum = 0.0;
    for(int i =0; i<m; i++)sum += recvBuf[i];
    float avg_proc = sum / m;

    MPI_Gather(&avg_proc, 1, MPI_FLOAT, recvArr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        sum = 0.0;
        for(int i =0; i<size; i++)sum += recvArr[i];
        printf("The Average of all elements is %f \n", sum/size);
    }
    
    MPI_Finalize();
    return 0;
}