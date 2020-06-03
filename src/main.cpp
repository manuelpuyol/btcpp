#include<cli.hpp>
#include<json.hpp>

#ifdef USE_CUDA
#include "mining.cuh"
#endif

int main() {
#ifdef USE_CUDA
  std::cout << gpuAdd(1,2) << std::endl;
#else
  CLI cli;

  cli.run();
#endif
}
