#include<header.hpp>

Header::Header(unsigned long _nonce, string _prev_hash, string _root) :
  nonce(_nonce),
  prev_hash(_prev_hash),
  merkle_root(_root) {
  hash = mine_hash(*this);
}

Header::Header(const ptree &json) :
  nonce(json.get<unsigned long>("nonce")),
  prev_hash(json.get<string>("prev_hash")),
  hash(json.get<string>("hash")),
  merkle_root(json.get<string>("merkle_root")) {}

ptree Header::to_json() const {
  ptree json;

  json.put("nonce", nonce);
  json.put("prev_hash", prev_hash);
  json.put("hash", hash);
  json.put("merkle_root", merkle_root);

  return json;
}

ostream &operator<<(ostream &os, const Header &h) {
  write_json(os, h.to_json());

  return os;
}

string to_string(const Header &header) {
  return header.prev_hash + header.merkle_root + to_string(header.nonce);
}
