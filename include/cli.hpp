#include<iostream>
#include<fstream>
#include<filesystem>
#include<vector>
#include<thread>
#include<future>
#include<boost/algorithm/string.hpp>
#include<boost/property_tree/json_parser.hpp>
#include<blockchain.hpp>
#include<transaction.hpp>
#include<miner.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::ofstream;
using std::ifstream;
using std::future;
using std::async;
using std::filesystem::path;
using boost::algorithm::to_lower;
using boost::property_tree::write_json;
using boost::property_tree::read_json;

#define HELP "help"
#define QUIT "quit"
#define CHANGE "change"
#define LOAD "load"
#define DUMP "dump"
#define PRINT "print"
#define CREATE "create"
#define MINE "mine"

class CLI {
public:
  CLI();

  void run();
private:
  Blockchain bc;
  vector<Transaction> transactions;
  bool running;

  void mine();
  void create();
  void load();
  void dump();
  void print();
  void change();
  void help();
  void quit();

  void load_blockchain();
  void load_transactions();
  void dump_blockchain();
  void dump_transactions();
  string root_path();

  bool compare_cmd(string &cmd, const string &action);
  void run_cmd(string &cmd);
};
