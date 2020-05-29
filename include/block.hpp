#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<header.hpp>
#include<transaction.hpp>
#include<merkle_tree.hpp>
#include<boost/variant.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::map;
using std::vector;
using std::string;
using std::move;
using std::ostream;
using boost::variant;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

typedef map<string, variant<const Header *, vector<Transaction>, unsigned int>> block_map;

class Block {
public:
  Block(Header &&_header);
  Block(Header &&_header, vector<Transaction> &&_transactions);
  Block(const ptree &json);

  Header header;
  vector<Transaction> transactions;
  unsigned int ntransactions;

  block_map get_map() const;
  bool is_valid();

  friend ostream &operator<<(ostream &os, const Block &b);
private:
  bool merkle_valid();
};

BOOST_FUSION_ADAPT_STRUCT(Block, header, transactions, ntransactions);

#endif
