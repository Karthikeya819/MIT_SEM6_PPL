#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    int len, chunk;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char S1[100], S2[100];

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        scanf("%s", S1);
        scanf("%s", S2);
        len = strlen(S1);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(len % size != 0){
        MPI_Finalize();
        return 0;
    }

    chunk = len / size;

    char localS1[chunk], localS2[chunk], localResult[2 * chunk];

    MPI_Scatter(S1, chunk, MPI_CHAR, localS1, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, chunk, MPI_CHAR, localS2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

    for(int i = 0, j = 0; i < chunk; i++){
        localResult[j++] = localS1[i];
        localResult[j++] = localS2[i];
    }

    char result[2 * len + 1];

    MPI_Gather(localResult, 2 * chunk, MPI_CHAR, result, 2 * chunk, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0){
        result[2 * len] = '\0';
        printf("Resultant String: %s\n", result);
    }

    MPI_Finalize();
    return 0;
}