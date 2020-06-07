#include<miner.hpp>
#include <chrono> 

Miner::Miner(vector<Transaction> &_transactions, const string &_prev_hash, unsigned int _difficulty, int _number_of_sha) :
  transactions(_transactions),
  found(false),
  difficulty(_difficulty),
  nonce(0),
  number_of_sha(_number_of_sha),
  prev_hash(_prev_hash) {
    sort(transactions.begin(), transactions.end());
    nthreads = thread::hardware_concurrency();
    bucket = MAX_NONCE / uint32_t(nthreads);
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
    bucket = MAX_NONCE / uint32_t(nthreads);
  };

bool Miner::mine() {
#ifdef USE_CUDA
  cout << "Starting mining pool using GPU" << endl;
#else
  cout << "Starting mining pool using " << nthreads << " threads" << endl;
#endif
  check_permutation();

  while(next_permutation(transactions.begin(), transactions.end()) && !found) {
    check_permutation();
  };

  return found;
}

void Miner::check_permutation() {
  vector<string> merkle_leaves;

  for(auto &t: transactions)
    merkle_leaves.push_back(t.hash);

  MerkleTree mt(merkle_leaves);
  root = mt.root;

  run_check();
}

void Miner::run_check() {
  #ifdef USE_CUDA
    gpu_check();
  #else
    cpu_check();
  #endif
}

#ifdef USE_CUDA
void Miner::gpu_check() {
  string test = prev_hash + root;
  tuple<int, uint32_t> res = cmine(test, difficulty);

  if(get<0>(res) == FOUND) {
    uint32_t n = get<1>(res);

    Hash hash(difficulty);
    hash.set_h(sha256(test + to_string(n), 2));

    // double check
    if(hash.is_valid()) {
      cout << "GPU found a block!" << endl;
      found = true;
      nonce = n;
      result = hash.h;
    }
  }
}
#else
void Miner::cpu_check() {
  vector<thread> threads;
  for(int i = 0; i < nthreads; i++)
    threads.emplace_back(&Miner::check_nonce, this, i + 1);

  for(auto &t: threads)
    t.join();
}

void Miner::check_nonce(int id) {
  uint32_t test = id * bucket;
  uint32_t end = (id + 1) * bucket;

  if(id == nthreads - 1) {
    end = MAX_NONCE;
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
#endif

#ifdef BENCHMARK
Miner::Miner() :
  found(false),
  difficulty(60),
  nonce(0),
  prev_hash("prev_hash"),
  root("root"),
  number_of_sha(2) {
    nthreads = thread::hardware_concurrency();
    bucket = MAX_NONCE / uint32_t(nthreads);
  };

void Miner::benchmark() {
  cout << "Will run " << MAX_NONCE << " hashes" << endl;
  auto start = high_resolution_clock::now();
  run_check();
  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(stop - start);
  auto milliseconds = duration.count();

  cout << "Took " << milliseconds << " milliseconds" << endl;
  cout << (MAX_NONCE / milliseconds) * 1000 << " Hashes per second" << endl;
}
#endif

ostream &operator<<(ostream &os, const Miner &m) {
  os << "Mining results:" << endl << endl;
  os << "Found: " << m.found << endl;
  os << "Nonce: " << m.nonce << endl;
  os << "Root: " << m.root << endl;
  os << "Hash: " << m.result << endl;

  return os;
}