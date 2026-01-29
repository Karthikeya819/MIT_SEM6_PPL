#include <stdio.h>
#include <mpi.h>

void mpi_error_to_str(int err_code, int rank) {
    if(err_code == MPI_SUCCESS)return;
    char err_str[MPI_MAX_ERROR_STRING];
    int result_len;
    MPI_Error_string(err_code, err_str, &result_len);
    printf("MPI Error, from %d: %s \n", rank, err_str);
}

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)printf("------Davasam Karthikeya, 230962326------\n");

    int fact = 1, recvBuf;
    for(int i=1; i<=rank+1; i++) fact = fact * i;

    int err = MPI_Scan(&fact, &recvBuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    mpi_error_to_str(err, rank);

    if(rank == size-1)
        printf("The sum of %d factorials is %d \n", size, recvBuf);

    MPI_Finalize();
    return 0;
}