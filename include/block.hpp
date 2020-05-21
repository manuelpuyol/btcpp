#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<header.hpp>
#include<transaction.hpp>
#include<boost/variant.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::map;
using std::vector;
using std::string;
using std::move;
using std::ostream;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

typedef map<string, variant<Header *, vector<Transaction>, unsigned int>> block_map;

class Block {
public:
  Block(Header &&_header);
  Block(Header &&_header, vector<Transaction> &&_transactions);
  Block(const ptree &json);

  Header header;
  vector<Transaction> transactions;
  unsigned int ntransactions;

  block_map members_map;

  block_map get_map() const;
  ptree to_json() const;

  friend ostream &operator<<(ostream &os, const Block &b);
};

BOOST_FUSION_ADAPT_STRUCT(Block, header, transactions, ntransactions);

block_map generate_map(Block &b);

#endif
