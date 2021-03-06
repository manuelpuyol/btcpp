#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include<iostream>
#include<vector>
#include<map>
#include<header.hpp>
#include<transaction.hpp>
#include<block.hpp>
#include<hash.hpp>
#include<boost/variant.hpp>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using std::map;
using std::cout;
using std::vector;
using std::move;
using std::ostream;
using boost::variant;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

typedef map<string, variant<vector<Block>, unsigned int>> blockchain_map;

class Blockchain {
public:
  Blockchain(unsigned int _difficulty);
  Blockchain(vector<Block> &&_blocks, unsigned int _difficulty);
  Blockchain(const ptree &json);

  vector<Block> blocks;
  unsigned int nblocks;
  unsigned int difficulty;

  void add_block(vector<Transaction> &&transactions, uint32_t nonce, string root, string hash, int number_of_sha);
  void add_initial_mock_block();

  string last_hash();
  blockchain_map get_map() const;
  bool is_valid();

  friend ostream &operator<<(ostream &os, const Blockchain &bc);
};

#endif
