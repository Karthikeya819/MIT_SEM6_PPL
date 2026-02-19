#include <cuda.h>
#include <stdio.h>

__global__ void convolution1D(int *N, int *M, int *P, int width, int mask_width){
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    if(i > width)return;
    
    float pval = 0;
    int start = i - (mask_width)/2;
    for(int j = 0; j < mask_width; j++){
        if(start + j >= 0 && start + j < width){
            pval += N[start + j]*M[j];
        }
    }
    P[i] = pval;
}


int main(){
    printf("------Davasam Karthikeya, 230962326------\n");

    int width, mask_width;
    printf("Enter width of Input arr: ");scanf("%d", &width);
    printf("Enter width of Mask arr: ");scanf("%d", &mask_width);

    int N[width], M[mask_width];
    for(int i = 0; i < width; i++) N[i] = 2 * i + 1;
    for(int i = 0; i < width; i++) M[i] = i;

    int *dM, *dN, *dP;
    cudaMalloc((void **)&dM, sizeof(int) * mask_width);
    cudaMalloc((void **)&dN, sizeof(int) * width);
    cudaMalloc((void **)&dP, sizeof(int) * width);

    cudaMemcpy(dM, &M[0], sizeof(int) * mask_width, cudaMemcpyHostToDevice);
    cudaMemcpy(dN, &N[0], sizeof(int) * width, cudaMemcpyHostToDevice);

    convolution1D<<<(width-1)/256 + 1, 256>>>(dN, dM, dP, width, mask_width);
    int P[width];
    cudaMemcpy(P, dP, sizeof(width) * width, cudaMemcpyDeviceToHost);

    for(int i =0; i < width; i++)printf("%d ", P[i]);
    printf("\n");

    cudaFree(dM);
    cudaFree(dN);
    cudaFree(dP);

    return 0;
}