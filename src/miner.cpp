#include<miner.hpp>

Miner::Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, int _number_of_sha) :
  transactions(_transactions),
  found(false),
  difficulty(_difficulty),
  nonce(0),
  number_of_sha(_number_of_sha),
  prev_hash(_prev_hash) {
    sort(transactions.begin(), transactions.end());
    nthreads = thread::hardware_concurrency();
    bucket = UINT32_MAX / uint32_t(nthreads);
  };

Miner::Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, unsigned int _nthreads, int _number_of_sha) :
  transactions(_transactions),
  found(false),
  difficulty(_difficulty),
  nonce(0),
  prev_hash(_prev_hash),
  number_of_sha(_number_of_sha),
  nthreads(_nthreads) {
    sort(transactions.begin(), transactions.end());
    bucket = UINT32_MAX / uint32_t(nthreads);
  };

bool Miner::mine() {
  cout << "Starting mining pool using " << nthreads << " threads" << endl;
  check_permutation();

  while(next_permutation(transactions.begin(), transactions.end()) && !found) {
    check_permutation();
  };

  return found;
}

void Miner::check_permutation() {
  vector<thread> threads;

  vector<string> merkle_leaves;

  for(auto &t: transactions)
    merkle_leaves.push_back(t.hash);

  MerkleTree mt(merkle_leaves);
  root = mt.root;

  for(int i = 0; i < nthreads; i++)
    threads.emplace_back(&Miner::check_nonce, this, i + 1);

  for(auto &t: threads)
    t.join();
}

void Miner::check_nonce(int id) {
  uint32_t test = id * bucket;
  uint32_t end = (id + 1) * bucket;

  if(id == nthreads - 1) {
    end = UINT32_MAX;
  }

  Hash hash(difficulty);
  string object;

  while(test < end && !found) {
    object = prev_hash + root + to_string(test);
    hash.set_h(sha256(object, number_of_sha));

    if(hash.is_valid()) {
      cout << "Thread " << id << " found a block!" << endl;
      std::unique_lock<std::shared_mutex> lock(mtx);
      found = true;
      nonce = test;
      result = hash.h;
    }

    test++;
  }
}

ostream &operator<<(ostream &os, const Miner &m) {
  os << "Mining results:" << endl << endl;
  os << "Found: " << m.found << endl;
  os << "Nonce: " << m.nonce << endl;
  os << "Root: " << m.root << endl;
  os << "Hash: " << m.result << endl;

  return os;
}