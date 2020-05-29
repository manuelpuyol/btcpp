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

ostream &operator<<(ostream &os, const Block &b) {
  write_json(os, to_json(b));

  return os;
}
