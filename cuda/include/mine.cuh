#ifndef MINE_CUH
#define MINE_CUH

#include<cuda.h>
#include<sha256.cuh>
#include<cmine.hpp>

#define NOT_FOUND -1
#define FOUND -1

__device__ void verify(BYTE *hash, int difficulty, int *result) {
  int aux = difficulty;
  int blocks = (difficulty + 1) / 2;

  for(int i = 0; i < blocks; i++) {
    unsigned char cmp;

    if(aux == 1) {
      cmp = 0x0F;
    } else {
      cmp = 0x00;
    }

    if(out[i] > cmp)
      return

    aux -= 2;
  }

  *result = 1
}

#endif   // MINE_CUH