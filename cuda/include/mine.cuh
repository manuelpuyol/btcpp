#ifndef MINE_CUH
#define MINE_CUH

#include<cuda.h>
#include<sha256.cuh>
#include<cmine.hpp>
#include<stdint.h>
#include<inttypes.h>

#define NOT_FOUND -1
#define FOUND 1
#define BLOCKS 1024
#define THREADS 1024
#define TOTAL BLOCKS * THREADS
#define BUCKET 4096

__device__ volatile unsigned char chars[11] = "0123456789";

__device__ BYTE uint32_to_byte(uint32_t val) {
  return chars[val];
}

__device__ BYTE *nonce_bytes(uint32_t nonce, int size) {
  BYTE *str = (BYTE*) malloc(size);

  for(int i = size - 1; i >= 0; i--) {
    str[i] = uint32_to_byte(nonce % 10);
    nonce /= 10;
  }

  return str;
}

__device__ int nonce_size(uint32_t nonce) {
    int size = 1;

    while (nonce /= 10)
      size++;

    return size;
}

__device__ BYTE *join_input_and_nonce(BYTE *input, uint32_t nonce, int size) {
  int nsize = nonce_size(nonce);
  int total_size = size + nsize;

  BYTE *nbytes = nonce_bytes(nonce, nsize);
  BYTE *bytes = (BYTE *) malloc(total_size);

  int i;

  for(i = 0; i < size; i++) {
    bytes[i] = input[i];
  }

  for(int j = 0; j < nsize; j++, i++) {
    bytes[i] = nbytes[j];
  }

  free(nbytes);

  return bytes;
}

__device__ bool verify(BYTE *input, uint32_t nonce, int size, int difficulty, int *result) {
  BYTE *hash = (BYTE *) malloc(SHA256_BLOCK_SIZE);
  BYTE *test = join_input_and_nonce(input, nonce, size);

  printf("test = %s\n", test);
  csha256(test, hash, size);

  int aux = difficulty;
  int blocks = (difficulty + 1) / 2;

  for(int i = 0; i < blocks; i++) {
    BYTE cmp;

    if(aux == 1) {
      cmp = 0x0F;
    } else {
      cmp = 0x00;
    }

    if(hash[i] > cmp)
      return false;

    aux -= 2;
  }

  *result = FOUND;

  free(hash);
  return true;
}

#endif   // MINE_CUH
