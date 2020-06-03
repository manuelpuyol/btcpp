#include<cli.hpp>
#include<json.hpp>

#ifdef USE_CUDA
#include "mining.cuh"
#endif

int main() {
  boost::filesystem::path p(__FILE__);
  std::cout << p.parent_path().parent_path().string() << endl;
#ifdef USE_CUDA
  std::cout << gpuAdd(1,2) << std::endl;
#else
  CLI cli;

  cli.run();
#endif
}
