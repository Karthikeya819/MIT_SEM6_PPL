#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[]){
    // ques cosnts
    int arr_size = 5;
    char word[] = "HELLO";

    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
        printf("------Davasam Karthikeya, 230962326------\n");

    if(rank < arr_size){
        char prev = word[rank];
        word[rank] = (word[rank] < 91) ? word[rank]+32: word[rank] - 32;
        printf("In ProcID: %d, letter is toggled from %c to %c \n", rank, prev, word[rank]);
    }

    MPI_Finalize();

}