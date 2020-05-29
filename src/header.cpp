#include<header.hpp>

Header::Header(unsigned long _nonce, string _prev_hash, string _root, int number_of_sha) :
  nonce(_nonce),
  prev_hash(_prev_hash),
  merkle_root(_root) {
  hash = sha256(*this, number_of_sha);
}

Header::Header(const ptree &json) :
  nonce(json.get<unsigned long>("nonce")),
  prev_hash(json.get<string>("prev_hash")),
  hash(json.get<string>("hash")),
  merkle_root(json.get<string>("merkle_root")) {}

header_map Header::get_map() const {
  header_map m;

  m["nonce"] = nonce;
  m["prev_hash"] = prev_hash;
  m["merkle_root"] = merkle_root;
  m["hash"] = hash;

  return m;
}

ostream &operator<<(ostream &os, const Header &h) {
  write_json(os, to_json(h));

  return os;
}

string to_string(const Header &header) {
  return header.prev_hash + header.merkle_root + to_string(header.nonce);
}
