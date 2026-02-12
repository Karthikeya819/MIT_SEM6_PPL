#include <cuda.h>
#include <stdio.h>

#define N 300

__global__ void findSin(float *a, float *b){
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    if(tid >= N)return;
    b[tid] = sinf(a[tid]);
}

int main(){
    float a[N], b[N];
    for(int i = 0; i < N; i++)a[i]=i;
    float *dA, *dB;

    int size = sizeof(float);

    printf("------Davasam Karthikeya, 230962326------\n");

    cudaMalloc((void **)&dA, N * size);
    cudaMalloc((void **)&dB, N * size);

    cudaMemcpy(dA, &a[0], N * size, cudaMemcpyHostToDevice);

    findSin<<<(N-1)/256 + 1, 256>>>(dA, dB);

    cudaMemcpy(b, dB, N * size, cudaMemcpyDeviceToHost);

    for(int i =0; i < N; i++)printf("%f ", b[i]);
    printf("\n");

    cudaFree(dA);
    cudaFree(dB);

    return 0;
}