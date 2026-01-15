#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        int num;
        scanf("%d", &num);

        MPI_Ssend(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&num, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Log: %d, Received back %d \n", rank, num);
    }else{
        int num;
        int dest = (rank == size-1)?0:rank+1;

        MPI_Recv(&num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        num++;
        MPI_Ssend(&num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}