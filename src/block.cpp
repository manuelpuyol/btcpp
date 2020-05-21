#include<block.hpp>

Block::Block(Header &&_header) : header(move(_header)), ntransactions(0) {
  members_map = generate_map(*this);
}

Block::Block(Header &&_header, vector<Transaction> &&_transactions) :
  header(move(_header)),
  transactions(move(_transactions)) {
  ntransactions = transactions.size();
  members_map = generate_map(*this);
}

Block::Block(const ptree &json) :
  header(json.get_child("header")),
  ntransactions(json.get<unsigned int>("ntransactions")) {
  for(auto &element: json.get_child("transactions"))
    transactions.push_back(element.second);
  members_map = generate_map(*this);
}

block_map Block::get_map() const {
  return members_map;
}

ostream &operator<<(ostream &os, const Block &b) {
  write_json(os, to_json(b));

  return os;
}

block_map generate_map(Block &b) {
  block_map m;

  m["header"] = &b.header;
  m["transactions"] = b.transactions;
  m["ntransactions"] = b.ntransactions;

  return m;
}

