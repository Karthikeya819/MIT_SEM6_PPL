#include <stdio.h>
#include <mpi.h>

void print_mpi_error(int err_code, int rank) {
    if(err_code == 0)return;
    char err_str[MPI_MAX_ERROR_STRING];
    int result_len;
    MPI_Error_string(err_code, err_str, &result_len);
    printf("MPI Error, from %d: %s \n", rank, err_str);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char strIn[size + 1], ch;
    if (rank == 0) {
        printf("------Davasam Karthikeya, 230962326------\n");
        scanf("%s", strIn);
    }

    MPI_Scatter(strIn, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    char sendBuf[size];
    for (int i = 0; i < size; i++) {
        if (i < rank + 1)
            sendBuf[i] = ch;
        else
            sendBuf[i] = '\0';
    }

    char recvBuf[size * size];

    MPI_Gather(sendBuf, size, MPI_CHAR, recvBuf, size, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Processed String: ");
        for (int i = 0; i < size * size; i++) {
            if (recvBuf[i] != '\0')
                printf("%c", recvBuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
