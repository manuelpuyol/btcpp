#ifndef BENCHMARK
#include<cli.hpp>
#include<json.hpp>
#else
#include<miner.hpp>
#endif

int main() {
#ifdef BENCHMARK
  Miner m;
  m.benchmark();
#else
  CLI cli;

  cli.run();
#endif
}
