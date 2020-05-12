#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<iostream>
#include<vector>
#include<string>
#include<header.hpp>
#include<transaction.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::vector;
using std::string;
using std::move;
using std::ostream;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

class Block {
public:
  Block(Header &&_header);
  Block(Header &&_header, vector<Transaction> &&_transactions);
  Block(const ptree &json);

  Header header;
  vector<Transaction> transactions;
  unsigned int ntransactions;

  ptree to_json() const;

  friend ostream &operator<<(ostream &os, const Block &b);
};

#endif
