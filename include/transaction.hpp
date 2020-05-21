#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include<iostream>
#include<string>
#include<random>
#include<map>
#include<hash.hpp>
#include<json.hpp>
#include<boost/variant.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::map;
using std::endl;
using std::string;
using std::to_string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ostream;
using boost::property_tree::ptree;
using boost::property_tree::write_json;
using boost::variant;

typedef map<string, variant<string, unsigned int>> transaction_map;

class Transaction {
public:
  Transaction(unsigned int _value);
  Transaction(const ptree &json);

  unsigned int value;
  string sender;
  string receiver;
  string hash;

  transaction_map members_map;

  transaction_map get_map() const;

  friend ostream &operator<<(ostream &os, const Transaction &t);
  const bool operator<(const Transaction &t);
  inline string to_string(const Transaction &transaction);
};

BOOST_FUSION_ADAPT_STRUCT(Transaction, value, sender, receiver, hash);

transaction_map generate_map(Transaction &t);

#endif
