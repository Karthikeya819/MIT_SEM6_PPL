#include <stdio.h>
#include <mpi.h>

int fact_number(int x){
    int ans = 1;
    while(x > 0){
        ans *= x;
        x--;
    }
    return ans;
}

int nthFibonacci(int n){
    if (n <= 1) return n;
    return nthFibonacci(n - 1) + nthFibonacci(n - 2);
}

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
        printf("------Davasam Karthikeya, 230962326------\n");

    if(rank % 2 == 0)
        printf("Fact(%d) is %d, from proc id:%d\n", rank, fact_number(rank), rank);
    else
        printf("Fib(%d) is %d, from proc id:%d\n", rank, nthFibonacci(rank), rank);
    
    MPI_Finalize();
}