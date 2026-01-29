#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[4][4];
    int row[4], scanRow[4];
    int result[4][4];

    if (rank == 0) {
        printf("------Davasam Karthikeya, 230962326------\n");
        printf("Enter 4x4 matrix:\n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &matrix[i][j]);
    }

    MPI_Scatter(matrix, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(row, scanRow, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(scanRow, 4, MPI_INT, result, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Output Matrix:\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                printf("%d ", result[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
