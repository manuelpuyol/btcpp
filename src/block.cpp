#include<block.hpp>

Block::Block(Header &&_header) : header(move(_header)), ntransactions(0) {}

Block::Block(Header &&_header, vector<Transaction> &&_transactions) :
  header(move(_header)),
  transactions(move(_transactions)) {
  ntransactions = transactions.size();
}

Block::Block(const ptree &json) :
  header(json.get_child("header")),
  ntransactions(json.get<unsigned int>("ntransactions")) {
  for(auto &element: json.get_child("transactions"))
    transactions.push_back(element.second);
}

block_map Block::get_map() const {
  block_map m;

  m["header"] = &header;
  m["transactions"] = transactions;
  m["ntransactions"] = ntransactions;

  return m;
}

bool Block::is_valid() {
  return header.is_valid() && merkle_valid();
}

bool Block::merkle_valid() {
  vector<string> merkle_leaves;

  for(auto &t: transactions)
    merkle_leaves.push_back(t.hash);

  MerkleTree mt(merkle_leaves);
  
  return mt.root.compare(header.merkle_root) == 0;
}

ostream &operator<<(ostream &os, const Block &b) {
  write_json(os, to_json(b));

  return os;
}
