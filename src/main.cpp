// #include<cli.hpp>
// #include<json.hpp>

#ifdef USE_CUDA
#include<cuda_sha256.hpp>
#endif

int main() {
#ifdef USE_CUDA
  cuda_sha256();
#else
  // CLI cli;

  // cli.run();
#endif
}
