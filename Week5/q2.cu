#include <cuda.h>
#include <stdio.h>

__global__ void add(int N, int *a, int *b, int *c){
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if(tid >= N)return;

    c[tid] = a[tid] + b[tid];
}

int main(){
    int N;
    printf("Enter the value of N:");
    scanf("%d", &N);

    int a[N], b[N], c[N];
    int *dA, *dB, *dC;
    for(int i = 0; i < N; i++){
        a[i] = i;
        b[i] = 2*i;
    }

    int size = sizeof(int);

    printf("------Davasam Karthikeya, 230962326------\n");

    cudaMalloc((void **)&dA, N * size);
    cudaMalloc((void **)&dB, N * size);
    cudaMalloc((void **)&dC, N * size);

    cudaMemcpy(dA, &a[0], N * size, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, &b[0], N * size, cudaMemcpyHostToDevice);

    int blocks = (N-1)/256 + 1;
    printf("Allocated %d blocks\n", blocks);

    add<<<blocks, 256>>>(N, dA, dB, dC);

    cudaMemcpy(c, dC, N * size, cudaMemcpyDeviceToHost);

    for(int i =0; i < N; i++)printf("%d ", c[i]);
    printf("\n");

    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dB);

    return 0;
}