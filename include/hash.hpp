#ifndef HASH_HPP
#define HASH_HPP

#include<string>
#include<sstream>
#include<iomanip>
#include<openssl/sha.h>

using std::string;
using std::stringstream;
using std::hex;
using std::setw;
using std::setfill;
using std::to_string;

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
string double_sha256(T object) {
  return sha256(sha256(object));
}

template<class T>
string mine_hash(T object) {
  return double_sha256(object);
}

#endif
