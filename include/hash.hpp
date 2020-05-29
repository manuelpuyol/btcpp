#ifndef HASH_HPP
#define HASH_HPP

#include<string>
#include<sstream>
#include<iomanip>
#include<iostream>
#include<regex>
#include<openssl/sha.h>

using std::cout;
using std::endl;
using std::string;
using std::regex;
using std::regex_search;
using std::stringstream;
using std::hex;
using std::setw;
using std::setfill;
using std::to_string;

class Hash {
public:
  Hash(int _difficulty) : difficulty(_difficulty) {
    stringstream ss;
    ss << "^0{" << _difficulty << "}|0{" << _difficulty << "}$";

    r = regex(ss.str());
  }

  string h;

  void set_h(const string &_h) {
    h = _h;
  }

  bool is_valid() {
    return regex_search(h, r);
  }

private:
  int difficulty;
  regex r;
};

template<class T>
string sha256(T object) {
  string str;
  if constexpr(std::is_same_v<T, std::string> || std::is_same_v<T, const char *>)
    str = object;
  else
    str = to_string(object);
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  stringstream ss;

  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);

  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    ss << hex << setw(2) << setfill('0') << (int)hash[i];

  return ss.str();
}

template<class T>
string sha256(T object, int n) {
  string h = sha256(object);

  for(auto i = 1; i < n; i++)
    h = sha256(h);

  return h;
}

template<class T>
string btc_hash(T object) {
  return sha256(sha256(object));
}

#endif
