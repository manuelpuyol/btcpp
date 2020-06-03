#include<cli.hpp>
#include<json.hpp>

#ifdef USE_CUDA
#include "mining.cuh"
#endif

int main() {
#ifdef USE_CUDA
  std::cout << "CUDA: On" << std::endl;
  printCudaVersion();
#else
  CLI cli;

  cli.run();
#endif
}
