#include<mine.cuh>

__global__ void mine(BYTE *in, BYTE *out, int *result, int size, int difficulty) {
  int id = (blockIdx.x * blockDim.x) + threadIdx.x;

  uint32_t test = id * BUCKET;
  uint32_t end = (id + 1) * BUCKET;

  if(id == TOTAL - 1) {
    end = UINT32_MAX;
  }

  printf("id = %d - start = %" PRIu32 " - end = %" PRIu32 "\n ", id, test, end);
  // csha256(in, out, size);
  // verify(out, difficulty, result);
}

void cmine(string str, int difficulty) {
  // host
  BYTE *buff = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
  int size = str.length();
  int res = NOT_FOUND;

  // device
  BYTE *in, *out;
  int *result;

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&out, SHA256_BLOCK_SIZE);
  cudaMalloc((void **)&result, sizeof(int));

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);
  cudaMemcpy(result, &res, sizeof(int), cudaMemcpyHostToDevice);

  pre_sha256();
  mine <<< BLOCKS, THREADS >>> (in, out, result, size, difficulty );

  cudaDeviceSynchronize();

  cudaMemcpy(&res, result, sizeof(int), cudaMemcpyDeviceToHost);

  cout << "result = " << res << endl;

  cudaFree(in);
  cudaFree(out);
  cudaFree(result);
}