#include <stdio.h>
#include <mpi.h>

int int_pow(int x, int power){
    int ans = 1;
    while(power >= 1){
        ans *= x;
        power -= 1;
    }
    return ans;
}

int main(int argc, char *argv[]){
    int x = 2;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
        printf("------Davasam Karthikeya, 230962326------\n");
    
    printf("Power(%d, %d) is %d, ann caluculated from process ID: %d \n", x, rank, int_pow(x, rank), rank);

    if(rank % 2 == 0){
        // even ranked proc
        printf("Hello, from proc id:%d \n", rank);
    }else{
        printf("World!, from proc id:%d \n", rank);
    }

    MPI_Finalize();

    return 0;
}