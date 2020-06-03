#include<mining.cuh>

__global__ void add(int *a, int *b, int *c) {
  *c = *a + *b;
}

int gpuAdd(int a, int b) {
  int c;

  int *d_a, *d_b, *d_c; // device copies of a, b, c
  int size = sizeof(int);

  // Allocate space for device copies of a, b, c
  cudaMalloc((void **)&d_a, size);
  cudaMalloc((void **)&d_b, size);
  cudaMalloc((void **)&d_c, size);

  cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
  // Launch add() kernel on GPU
  add<<<1,1>>>(d_a, d_b, d_c);
  // Copy result back to host
  cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  // Cleanup
  cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

  return c;
}
