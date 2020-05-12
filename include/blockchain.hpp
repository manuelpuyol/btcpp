#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include<iostream>
#include<vector>
#include<header.hpp>
#include<transaction.hpp>
#include<block.hpp>
#include<hash.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::cout;
using std::vector;
using std::move;
using std::ostream;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

class Blockchain {
public:
  Blockchain(unsigned int _difficulty);
  Blockchain(vector<Block> &&_blocks, unsigned int _difficulty);
  Blockchain(const ptree &json);

  vector<Block> blocks;
  unsigned int nblocks;
  unsigned int difficulty;

  void add_block(vector<Transaction> &&transactions, unsigned long nonce, string root, string hash);
  void add_initial_mock_block();

  string last_hash();
  ptree to_json() const;

  friend ostream &operator<<(ostream &os, const Blockchain &bc);
};

#endif
