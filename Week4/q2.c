#include <stdio.h>
#include <mpi.h>

void print_mpi_error(int err_code, int rank) {
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

    int Mat[3][3], searchElem;
    if(rank == 0){
        printf("------Davasam Karthikeya, 230962326------\n");
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                scanf("%d", &Mat[i][j]);
            }
        }
        scanf("%d", &searchElem);
    }
    int err = MPI_Bcast(&searchElem, 1, MPI_INT, 0, MPI_COMM_WORLD);
    print_mpi_error(err, rank);
    err = MPI_Scatter(&Mat, 3, MPI_INT, &Mat[0], 3, MPI_INT, 0, MPI_COMM_WORLD);
    print_mpi_error(err, rank);

    int count = 0, recvBuf;
    for(int i = 0; i< 3; i++){
        if(Mat[0][i] == searchElem)count++;
    }

    MPI_Reduce(&count, &recvBuf, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("The number of occurances of %d in Mat is %d \n", searchElem ,recvBuf);
    }

    MPI_Finalize();
    return 0;
}