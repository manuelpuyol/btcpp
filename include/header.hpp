#ifndef HEADER_HPP
#define HEADER_HPP

#include<iostream>
#include<string>
#include<hash.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::endl;
using std::move;
using std::string;
using std::to_string;
using std::ostream;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

class Header {
public:
  Header(unsigned long _nonce, string _prev_hash, string _root);
  Header(const ptree &json);

  unsigned long nonce;
  string prev_hash;
  string hash;
  string merkle_root;

  ptree to_json() const;

  friend ostream &operator<<(ostream &os, const Header &h);
  inline string to_string(const Header &header);
};

#endif
