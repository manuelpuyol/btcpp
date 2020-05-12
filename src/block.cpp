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

ptree Block::to_json() const {
  ptree json;
  ptree jheader = header.to_json();
  ptree jtransactions;

  for (auto &transaction : transactions)
    jtransactions.push_back(std::make_pair("", transaction.to_json()));

  json.put("ntransactions", ntransactions);
  json.add_child("header", jheader);
  json.add_child("transactions", jtransactions);

  return json;
}

ostream &operator<<(ostream &os, const Block &b) {
  write_json(os, b.to_json());

  return os;
}
