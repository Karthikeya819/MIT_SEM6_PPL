#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int x = 2, y = 3;

    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
        printf("------Davasam Karthikeya, 230962326------\n");

    switch(rank){
        case 0:
            printf("Value of x+y is %d, from proc 0\n", x+y);
        break;
        case 1:
            printf("Value of x-y is %d, from proc 1\n", x-y);
        break;
        case 2:
            printf("Value of x*y is %d, from proc 2\n", x*y);
        break;
        case 3:
            printf("Value of x/y is %f, from proc 3\n", ((float)x)/y);
        break;
    }
    
    MPI_Finalize();
}