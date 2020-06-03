// cd /home/hork/cuda-workspace/CudaSHA256/Debug/files
// time ~/Dropbox/FIIT/APS/Projekt/CpuSHA256/a.out -f ../file-list
// time ../CudaSHA256 -f ../file-list

#include<sha256.cuh>

__global__ void sha256_cuda(JOB *job) {
  // perform sha256 calculation here
  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, job->data, job->size);
  sha256_final(&ctx, job->digest);
}

void pre_sha256() {
  checkCudaErrors(cudaMemcpyToSymbol(dev_k, host_k, sizeof(host_k), 0, cudaMemcpyHostToDevice));
}


void runJob(JOB *job){
  sha256_cuda <<< 1, 1 >>> (job);
}


JOB *JOB_init(BYTE *data, long size) {
  JOB *j;
  checkCudaErrors(cudaMallocManaged(&j, sizeof(JOB)));	//j = (JOB *)malloc(sizeof(JOB));
  checkCudaErrors(cudaMallocManaged(&(j->data), size));
  j->data = data;
  j->size = size;
  for (int i = 0; i < 64; i++) {
    j->digest[i] = 0xff;
  }

  return j;
}


void cuda_sha256() {
  BYTE *buff = (BYTE *) "lol";
  JOB *job;

  checkCudaErrors(cudaMallocManaged(&job, sizeof(JOB)));
  job = JOB_init(buff, sizeof(buff));

  pre_sha256();
  runJob(job);

  print_job(job);

  cudaDeviceSynchronize();
  cudaDeviceReset();
}