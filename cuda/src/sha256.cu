#include<sha256.cuh>

__global__ void sha256_cuda(BYTE *in, BYTE *out, int size) {
  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, in, size);
  sha256_final(&ctx, out);
  printf("\n");
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    printf("%.2x", out[i]);
  }
  printf("\n");
}

void pre_sha256() {
  checkCudaErrors(cudaMemcpyToSymbol(dev_k, host_k, sizeof(host_k), 0, cudaMemcpyHostToDevice));
}

void cuda_sha256() {
  std::string str = "lol";
  BYTE *buff = reinterpret_cast<unsigned char*>(const_cast<char*>(str.c_str()));
  BYTE *result = (BYTE *) malloc(SHA256_BLOCK_SIZE);

  int size = str.length();
  BYTE *in, *out;

  cudaMalloc((void **)&in, size);
  cudaMalloc((void **)&out, SHA256_BLOCK_SIZE);

  cudaMemcpy(in, buff, size * sizeof(BYTE), cudaMemcpyHostToDevice);

  pre_sha256();
  sha256_cuda <<< 1, 1 >>> (in, out, size);

  cudaDeviceSynchronize();
  cudaMemcpy(result, out, SHA256_BLOCK_SIZE, cudaMemcpyDeviceToHost);
  printf("result = %s\n", result);

  char * string = (char *)malloc(70);
  int k, i;
  for (i = 0, k = 0; i < SHA256_BLOCK_SIZE; i++, k+= 2) {
    sprintf(string + k, "%.2x", result[i]);
  }
  string[64] = 0;
  
  printf("hash = %s\n", string);
  free(string);
  cudaFree(in);
  cudaFree(out);
  
}