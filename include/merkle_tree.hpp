#ifndef MERKLE_TREE_HPP
#define MERKLE_TREE_HPP

#include<iostream>
#include<vector>
#include<string>
#include<transaction.hpp>

using std::vector;
using std::string;
using std::move;

class MerkleTree {
public:
  MerkleTree(const vector<Transaction> &transactions);
  MerkleTree(const vector<string> &leaves);

  string root;

private:
  vector<string> leaves;

  string calculate_root();
  vector<string> calculate_next_level(const vector<string> &nodes);
};


#endif
