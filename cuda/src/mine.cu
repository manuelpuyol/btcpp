#include<mine.cuh>

__global__ void mine(BYTE *in, int *result, uint32_t *nonce, int size, int difficulty) {
  int id = (blockIdx.x * blockDim.x) + threadIdx.x;

  uint32_t test = 12345;
  uint32_t end = (id + 1) * BUCKET;

  if(id == TOTAL - 1) {
    end = UINT32_MAX;
  }

  if(verify(in, test, size, difficulty, result)) {
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
  BYTE *in;
  int *result;
  uint32_t *nonce;
  
  uint32_t x = 1234;
  int length = snprintf( NULL, 0, "%" PRIu32, x );

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&result, sizeof(int));
  cudaMalloc((void **)&nonce, sizeof(uint32_t));

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);
  cudaMemcpy(result, &res, sizeof(int), cudaMemcpyHostToDevice);

  pre_sha256();
  mine<<< 1, 1 >>>(in, result, nonce, size, difficulty);

  cudaDeviceSynchronize();

  cudaMemcpy(&res, result, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&n, nonce, sizeof(uint32_t), cudaMemcpyDeviceToHost);

  cout << "result = " << res << endl;
  cout << "nonce = " << n << endl;

  cudaFree(in);
  cudaFree(result);
  cudaFree(nonce);

  return n;
}
