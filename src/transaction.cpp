#include<transaction.hpp>

Transaction::Transaction(unsigned int _value) : value(_value) {
  random_device rd;
  mt19937 eng(rd());
  std::uniform_int_distribution<int> distr(0, 10'000'000);

  sender = sha256(distr(eng));
  receiver = sha256(distr(eng));
  hash = sha256(*this);
}

Transaction::Transaction(const ptree &json) :
  value(json.get<unsigned int>("value")),
  sender(json.get<string>("sender")),
  receiver(json.get<string>("receiver")),
  hash(json.get<string>("hash")) {}

transaction_map Transaction::get_map() const {
  transaction_map m;

  m["sender"] = sender;
  m["receiver"] = receiver;
  m["hash"] = hash;
  m["value"] = value;

  return m;
}

const bool Transaction::operator<(const Transaction &t) {
  return (hash < t.hash);
}

ostream &operator<<(ostream &os, const Transaction &t) {
  write_json(os, to_json(t));

  return os;
}

string to_string(const Transaction &transaction) {
  return transaction.sender + transaction.receiver + to_string(transaction.value);;
}
