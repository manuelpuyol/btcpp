#include<sha256.cuh>

__global__ void sha256_cuda(BYTE *in, BYTE *out, int size, int difficulty, int *result) {
  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, in, size);
  sha256_final(&ctx, out);

  int aux = difficulty;
  int blocks = (difficulty + 1) / 2;

  *result = 1;
  for(int i = 0; i < blocks; i++) {
    unsigned char cmp;

    if(aux == 1) {
      cmp = 0x0F;
    } else {
      cmp = 0x00;
    }

    if(out[i] > cmp && out[SHA256_BLOCK_SIZE - 1 - i] > cmp)
      *result = -1;

    aux -= 2;
  }
}

void pre_sha256() {
  checkCudaErrors(cudaMemcpyToSymbol(dev_k, host_k, sizeof(host_k), 0, cudaMemcpyHostToDevice));
}

void cuda_sha256(string str, int difficulty) {
  BYTE *buff = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));

  int size = str.length();
  int res;
  BYTE *in, *out;
  int *result;

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&out, SHA256_BLOCK_SIZE);
  cudaMalloc((void **)&result, sizeof(int));

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);

  pre_sha256();
  sha256_cuda <<< 1, 1 >>> (in, out, size, difficulty, result);

  cudaDeviceSynchronize();

  cudaMemcpy(&res, result, sizeof(int), cudaMemcpyDeviceToHost);

  cout << "result = " << res << endl;

  cudaFree(in);
  cudaFree(out);
  cudaFree(result);
}