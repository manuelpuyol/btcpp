#ifndef MINER_HPP
#define MINER_HPP

#include<iostream>
#include<string>
#include<thread>
#include<shared_mutex>
#include<vector>
#include<climits>
#include<algorithm>
#include<hash.hpp>
#include<merkle_tree.hpp>
#include<transaction.hpp>

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
  Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty);
  Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, unsigned int _nthreads);

  bool found;
  unsigned long nonce;
  string result;
  string root;

  bool mine();
  friend ostream &operator<<(ostream &os, const Miner &m);
private:
  string prev_hash;

  vector<Transaction> transactions;
  unsigned int difficulty;
  unsigned int nthreads;
  unsigned long bucket;

  shared_mutex mutable mtx;

  void check_permutation();
  void check_nonce(int id);

  template<class T>
  virtual string mining_hash(T object) = 0;
};

class SSHAMiner : Miner {
private:
  template<class T>
  string mining_hash(T object) {
    return sha256(object);
  }
}

class BTCMiner : Miner {
private:
  template<class T>
  string mining_hash(T object) {
    return btc_hash(object);
  }
}

class TSHAMiner : Miner {
private:
  template<class T>
  string mining_hash(T object) {
    return sha256(sha256(sha256(object));;
  }
}

#endif
