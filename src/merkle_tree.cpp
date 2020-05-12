#include<merkle_tree.hpp>

MerkleTree::MerkleTree(const vector<Transaction> &transactions) {
  for(auto t: transactions)
    leaves.push_back(t.hash);

  root = calculate_root();
}

MerkleTree::MerkleTree(const vector<string> &_leaves) : leaves(_leaves) {
  root = calculate_root();
}

string MerkleTree::calculate_root() {
  vector<string> parents = leaves;

  while(parents.size() > 1) {
    parents = calculate_next_level(parents);
  }

  return parents[0];
}

vector<string> MerkleTree::calculate_next_level(const vector<string> &nodes) {
  vector<string> parents;

  int size = nodes.size();

  for(auto i = 0; i < size; i += 2) {
    string left_hash = nodes[i];
    string right_hash = (i+1 == size) ? "" : nodes[i+1];

    parents.push_back(sha256(left_hash + right_hash));
  }

  return parents;
}