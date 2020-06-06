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

__device__ bool verify(BYTE *hash, int difficulty, int *result) {
  int aux = difficulty;
  int blocks = (difficulty + 1) / 2;

  for(int i = 0; i < blocks; i++) {
    unsigned char cmp;

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
  return true;
}

#endif   // MINE_CUH
