#include <cuda.h>
#include <stdio.h>

#define N 200

__global__ void add(int *a, int *b, int *c){
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    c[tid] = a[tid] + b[tid];
}

int main(){
    int a[N], b[N], c[N];
    for(int i=0; i < N; i++){
        a[i] = i;
        b[i] = 2*i;
    }
    int *dA, *dB, *dC;

    int size = sizeof(int);

    printf("------Davasam Karthikeya, 230962326------\n");

    cudaMalloc((void **)&dA, N * size);
    cudaMalloc((void **)&dB, N * size);
    cudaMalloc((void **)&dC, N * size);

    cudaMemcpy(dA, &a[0], N * size, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, &b[0], N * size, cudaMemcpyHostToDevice);

    add<<<1,N>>>(dA, dB, dC);

    cudaMemcpy(c, dC, N * size, cudaMemcpyDeviceToHost);

    for(int i =0; i < N; i++)printf("%d ", c[i]);
    printf("\n");

    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dB);

    return 0;
}