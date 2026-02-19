#include <cuda.h>
#include <stdio.h>

__global__ void oddEvenSort(int *Arr, int size, int label){
    int gtid = blockIdx.x * blockDim.x + threadIdx.x;
    if (gtid >= size - 1) return;

    if(gtid < size && (gtid % 2) != label)return;

    if(Arr[gtid] > Arr[gtid + 1]){
        int temp = Arr[gtid];
        Arr[gtid] = Arr[gtid + 1];
        Arr[gtid + 1] = temp;
    }
}


int main(){
    printf("------Davasam Karthikeya, 230962326------\n");

    int size;
    printf("Enter size of Arr: ");scanf("%d", &size);

    int Arr[size];
    for(int i = 0; i < size; i++)Arr[i] = rand() % 1000;

    int *dArr;
    cudaMalloc((void **)&dArr, sizeof(int) * size);

    cudaMemcpy(dArr, &Arr[0], sizeof(int) * size, cudaMemcpyHostToDevice);
    for(int i =0; i < size; i++){
        oddEvenSort<<<(size-1)/256 + 1, 256>>>(dArr, size, i % 2);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(Arr, dArr, sizeof(int) * size, cudaMemcpyDeviceToHost);


    for(int i =0; i < size; i++)printf("%d ", Arr[i]);
    printf("\n");

    cudaFree(dArr);

    return 0;
}