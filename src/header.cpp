#include<header.hpp>

Header::Header(unsigned long _nonce, string _prev_hash, string _root) :
  nonce(_nonce),
  prev_hash(_prev_hash),
  merkle_root(_root) {
  hash = btc_hash(*this);

  members_map = generate_map(*this);
}

Header::Header(const ptree &json) :
  nonce(json.get<unsigned long>("nonce")),
  prev_hash(json.get<string>("prev_hash")),
  hash(json.get<string>("hash")),
  merkle_root(json.get<string>("merkle_root")) {
    members_map = generate_map(*this);
  }

header_map Header::get_map() const {
  return members_map;
}

ostream &operator<<(ostream &os, const Header &h) {
  write_json(os, to_json(h));

  return os;
}

string to_string(const Header &header) {
  return header.prev_hash + header.merkle_root + to_string(header.nonce);
}

header_map generate_map(Header &h) {
  header_map m;

  m["nonce"] = h.nonce;
  m["prev_hash"] = h.prev_hash;
  m["merkle_root"] = h.merkle_root;
  m["hash"] = h.hash;

  return m;
}
