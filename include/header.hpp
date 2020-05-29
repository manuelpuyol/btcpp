#ifndef HEADER_HPP
#define HEADER_HPP

#include<iostream>
#include<string>
#include<map>
#include<hash.hpp>
#include<json.hpp>
#include<boost/variant.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::endl;
using std::move;
using std::map;
using std::string;
using std::to_string;
using std::ostream;
using boost::variant;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

typedef map<string, variant<string, unsigned long>> header_map;

class Header {
public:
  Header(unsigned long _nonce, string _prev_hash, string _root, int _number_of_sha);
  Header(const ptree &json);

  unsigned long nonce;
  string prev_hash;
  string hash;
  string merkle_root;
  int number_of_sha;

  header_map get_map() const;
  bool is_valid();

  friend ostream &operator<<(ostream &os, const Header &h);
  inline string to_string(const Header &header);
};

BOOST_FUSION_ADAPT_STRUCT(Header, nonce, prev_hash, hash, merkle_root);

#endif
