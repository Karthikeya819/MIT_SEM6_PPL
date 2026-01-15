#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status st1;

    if(rank == 0){
        char word[] = "HeLLoWoRld";
        int word_len = strlen(word);

        printf("------Davasam Karthikeya, 230962326------\n");

        // send word count first
        MPI_Ssend(&word_len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Send Word
        MPI_Ssend(&word, word_len + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Log: %d, Sent the word: %s from 0 \n", rank, word);
        // Recv processed word
        MPI_Recv(&word, word_len + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &st1);
        printf("Log: %d, Received processed word: %s from 1 \n", rank, word);

        

    }else if(rank == 1){
        int word_len;

        // Recv Word_len
        MPI_Recv(&word_len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st1);

        // Recv Word
        char word[word_len + 1];
        MPI_Recv(&word, word_len + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &st1);

        // Toggling
        for(int i =0; i< word_len; i++)
            word[i] = (word[i] < 91) ? word[i]+32: word[i] - 32;

        // Sending it back to rank:0
        MPI_Ssend(&word, word_len + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}