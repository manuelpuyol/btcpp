#include<mine.cuh>

__global__ void mine(BYTE *in, BYTE *out, int *result, uint32_t *nonce, int size, int difficulty) {
  int id = (blockIdx.x * blockDim.x) + threadIdx.x;

  uint32_t test = id * BUCKET;
  uint32_t end = (id + 1) * BUCKET;

  if(id == TOTAL - 1) {
    end = UINT32_MAX;
  }

  csha256(in, out, size);
  if(verify(out, difficulty, result)) {
    *nonce = test;
  }
}

uint32_t cmine(string str, int difficulty) {
  // host
  BYTE *buff = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
  int size = str.length();
  int res = NOT_FOUND;
  uint32_t n;

  // device
  BYTE *in, *out;
  int *result;
  uint32_t *nonce;

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&out, SHA256_BLOCK_SIZE);
  cudaMalloc((void **)&result, sizeof(int));
  cudaMalloc((void **)&nonce, sizeof(uint32_t));

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);
  cudaMemcpy(result, &res, sizeof(int), cudaMemcpyHostToDevice);

  pre_sha256();
  mine<<< 1, 1 >>>(in, out, result, nonce, size, difficulty);

  cudaDeviceSynchronize();

  cudaMemcpy(&res, result, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&n, nonce, sizeof(uint32_t), cudaMemcpyDeviceToHost);

  cout << "result = " << res << endl;
  cout << "nonce = " << n << endl;

  cudaFree(in);
  cudaFree(out);
  cudaFree(result);
  cudaFree(nonce);

  return n;
}
