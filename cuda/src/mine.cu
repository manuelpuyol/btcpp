#include<mine.cuh>

__global__ void mine(BYTE *in, BYTE *out, int size, int difficulty, int *result) {
  int id = (blockIdx.x * blockDim.x) + threadIdx.x;

  printf("id = %d\n ", id);
  // csha256(in, out, size);
  // verify(out, difficulty, result);
}

void cmine(string str, int difficulty) {
  BYTE *buff = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));

  int size = str.length();
  int res = NOT_FOUND;
  BYTE *in, *out;
  int *result;

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&out, SHA256_BLOCK_SIZE);
  cudaMalloc((void **)&result, sizeof(int));

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);
  cudaMemcpy(result, &res, sizeof(int), cudaMemcpyHostToDevice);

  pre_sha256();
  mine <<< BLOCKS, THREADS >>> (in, out, size, difficulty, result);

  cudaDeviceSynchronize();

  cudaMemcpy(&res, result, sizeof(int), cudaMemcpyDeviceToHost);

  cout << "result = " << res << endl;

  cudaFree(in);
  cudaFree(out);
  cudaFree(result);
}