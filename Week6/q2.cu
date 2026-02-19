#include <cuda.h>
#include <stdio.h>

__global__ void selectionSort(int *Arr, int *Out, int size){
    int gtid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gtid >= size) return;

    int pos = 0;
    for (int i = 0; i < size; i++){
        if (Arr[i] < Arr[gtid] || (Arr[i] == Arr[gtid] && i < gtid)){
            pos++;
        }
    }
    Out[pos] = Arr[gtid];
}


int main(){
    printf("------Davasam Karthikeya, 230962326------\n");

    int size;
    printf("Enter size of Arr: ");scanf("%d", &size);

    int Arr[size], Out[size];
    for(int i = 0; i < size; i++)Arr[i] = rand() % 1000;

    int *dArr, *dOut;

    cudaMalloc((void **)&dArr, sizeof(int) * size);
    cudaMalloc((void **)&dOut, sizeof(int) * size);


    cudaMemcpy(dArr, &Arr[0], sizeof(int) * size, cudaMemcpyHostToDevice);

    selectionSort<<<(size-1)/256 + 1, 256>>>(dArr, dOut, size);

    cudaMemcpy(Out, dOut, sizeof(int) * size, cudaMemcpyDeviceToHost);

    for(int i =0; i < size; i++)printf("%d ", Out[i]);
    printf("\n");

    cudaFree(dArr);
    cudaFree(dOut);

    return 0;
}