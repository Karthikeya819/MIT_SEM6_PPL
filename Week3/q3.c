#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int isConsonant(char ch){
    switch(ch){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return 0;
        break;
    }
    return 1;
}

int main(int argc, char *argv[]){
    int size, rank, n;
    char str1[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        scanf("%s", str1);
        n = strlen(str1);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(n % size != 0){
        if(rank == 0)printf("The len of string is not a Multiple of N \n");
        MPI_Finalize();
        return 0;
    }
    n /= size;

    char recvStr[n+1];
    MPI_Scatter(str1, n, MPI_CHAR, recvStr, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    recvStr[n] = '\0';

    int Conscount = 0;
    for(int i =0; i < n; i++)Conscount += isConsonant(recvStr[i]);

    int recvCount[size];
    MPI_Gather(&Conscount, 1, MPI_INT, recvCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int sum = 0;
        for(int i = 0;i < size; i++)sum += recvCount[i];
        printf("The total no of Consonants are %d \n", sum);
    }

    MPI_Finalize();
    return 0;
}