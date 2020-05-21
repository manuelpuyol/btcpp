#include<transaction.hpp>

Transaction::Transaction(unsigned int _value) : value(_value) {
  random_device rd;
  mt19937 eng(rd());
  std::uniform_int_distribution<int> distr(0, 10'000'000);

  sender = sha256(distr(eng));
  receiver = sha256(distr(eng));
  hash = sha256(*this);
  members_map = generate_map(*this);
}

Transaction::Transaction(const ptree &json) :
  value(json.get<unsigned int>("value")),
  sender(json.get<string>("sender")),
  receiver(json.get<string>("receiver")),
  hash(json.get<string>("hash")) {}

ptree Transaction::to_json() const {
  ptree json;

  json.put("value", value);
  json.put("sender", sender);
  json.put("receiver", receiver);
  json.put("hash", hash);

  return json;
}

const bool Transaction::operator<(const Transaction &t) {
  return (hash < t.hash);
}

ostream &operator<<(ostream &os, const Transaction &t) {
  write_json(os, t.to_json());

  return os;
}

string to_string(const Transaction &transaction) {
  return transaction.sender + transaction.receiver + to_string(transaction.value);;
}

transaction_map generate_map(Transaction &t) {
  transaction_map m;

  m["sender"] = t.sender;
  m["receiver"] = t.receiver;
  m["hash"] = t.hash;
  m["value"] = t.value;

  return m;
}
