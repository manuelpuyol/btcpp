#include<cli.hpp>
#include<json.hpp>

#ifdef USE_CUDA
#include<cmine.hpp>
#endif

int main() {
#ifdef USE_CUDA
  cmine("8e3b03f9c2e60bb03a225f3be4d63a4a08445d34e76712e0667fad8d6000f4722305843009213694060", 1);
  // cmine("8e3b03f9c2e60bb03a225f3be4d63a4a08445d34e76712e0667fad8d6000f4722305843009213694060", 2);
  // cmine("8e3b03f9c2e60bb03a225f3be4d63a4a08445d34e76712e0667fad8d6000f4722305843009213694060", 3);
  // cmine("8e3b03f9c2e60bb03a225f3be4d63a4a08445d34e76712e0667fad8d6000f4722305843009213694060", 4);
#else
  CLI cli;

  cli.run();
#endif
}
