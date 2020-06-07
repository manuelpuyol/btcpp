#ifndef MINER_HPP
#define MINER_HPP

#include<iostream>
#include<string>
#include<thread>
#include<shared_mutex>
#include<vector>
#include<stdint.h>
#include<algorithm>
#include<hash.hpp>
#include<merkle_tree.hpp>
#include<transaction.hpp>

#ifdef USE_CUDA
#include<cmine.hpp>
#include<tuple>

using std::tuple;
using std::get;
#endif

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::ref;
using std::shared_mutex;
using std::unique_lock;
using std::sort;
using std::next_permutation;
using std::ostream;
using std::to_string;

class Miner {
public:
  Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, int _number_of_sha);
  Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, unsigned int _nthreads, int _number_of_sha);

  bool found;
  uint32_t nonce;
  string result;
  string root;

  bool mine();
  friend ostream &operator<<(ostream &os, const Miner &m);
private:
  string prev_hash;

  vector<Transaction> transactions;
  unsigned int difficulty;
  unsigned int nthreads;
  uint32_t bucket;
  int number_of_sha;

  shared_mutex mutable mtx;

  void check_permutation();
  void cpu_check();
#ifdef USE_CUDA
  void gpu_check();
#endif
  void check_nonce(int id);

  string mining_hash(string object);
};

#endif
