#include<cli.hpp>

CLI::CLI() : running(true), bc(5), number_of_sha(2) {}

void CLI::run() {
  string cmd;

  help();

  while(running) {
    cout << ">$ ";
    cin >> cmd;

    run_cmd(cmd);
  }
}

void CLI::mine() {
  if(transactions.size() < 1) {
    cout << "You need at least one transaction" << endl;
    cout << "Use the command " << CREATE << " to create one" << endl;

    return;
  }

  Miner m(transactions, bc.last_hash(), bc.difficulty, number_of_sha);

  future<bool> result = async(&Miner::mine, &m);

  if(bc.difficulty > 5) {
    cout << "Your difficulty is higher than 5" << endl;
    cout << "This process may take a while" << endl;
  }

  if(result.get())
    bc.add_block(move(transactions), m.nonce, m.root, m.result, number_of_sha);
  else
    cout << "Miner could not find a valid block" << endl;
}

void CLI::create() {
  unsigned int value;
  cin >> value;

  if(cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "Invalid input" << endl;

    return;
  }

  transactions.push_back(Transaction(value));
  cout << "Transaction created" << endl;
}

void CLI::load() {
  load_blockchain();
  load_transactions();
}

void CLI::load_blockchain() {
  string path = root_path() + "/files/blockchain.json";

  ifstream file(path);

  if(!file.is_open()) {
    cout << "Error opening file: " << path << endl;
    return;
  }

  ptree json;
  read_json(file, json);

  bc = json;

  file.close();
  cout << "Blockchain load success" << endl;
}

void CLI::load_transactions() {
  string path = root_path() + "/files/transactions.json";

  ifstream file(path);

  if(!file.is_open()) {
    cout << "Error opening file: " << path << endl;
    return;
  }

  ptree json;
  read_json(file, json);

  transactions.clear();
  for(auto &element: json.get_child("transactions"))
    transactions.push_back(element.second);

  file.close();
  cout << "Transactions load success" << endl;
}

void CLI::dump() {
  dump_blockchain();
  dump_transactions();
}

void CLI::print() {
  cout << "Blockchain:" << endl << endl;
  cout << bc << endl;

  cout << endl << "========================" << endl << endl;
  cout << "Transactions:" << endl << endl;
  for(auto &t: transactions)
    cout << t << endl;
}

void CLI::dump_blockchain() {
  string path = root_path() + "/files/blockchain.json";

  ofstream ostrm(path);

  if(!ostrm.is_open()) {
    cout << "Error opening file: " << path << endl;
    return;
  }

  write_json(ostrm, to_json(bc));
  ostrm.close();
  cout << "Blockchain dump success" << endl;
}

void CLI::dump_transactions() {
  string path = root_path() + "/files/transactions.json";

  ofstream ostrm(path);

  if(!ostrm.is_open()) {
    cout << "Error opening file: " << path << endl;
    return;
  }

  ptree json;
  ptree aux;
  for(auto &t: transactions)
    aux.push_back(std::make_pair("", to_json(t)));

  json.add_child("transactions", aux);
  write_json(ostrm, json);

  ostrm.close();
  cout << "Transactions dump success" << endl;
}

string CLI::root_path() {
  return path(__FILE__).parent_path().parent_path().string();
}

void CLI::change() {
  unsigned int diff;
  cin >> diff;

  if(cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "Invalid input" << endl;

    return;
  }

  bc.difficulty = diff;
  cout << "Difficulty change success" << endl;
}

void CLI::sha() {
  unsigned int sha;
  cin >> sha;

  if(cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "Invalid input" << endl;

    return;
  }

  number_of_sha = sha;
  cout << "Number of SHA changed successfully" << endl;
}

void CLI::help() {
  cout << endl << "Welcome to my MPCS 51044 final project - BTC++!" << endl;
  cout << "This is a program developed by Manuel Puyol" << endl << endl;
  cout << "=============================================================" << endl << endl;
  cout << "Here are the available commands you may use:" << endl << endl;
  cout << MINE << " - starts the btc++ miner" << endl;
  cout << CREATE << " {value} - creates a mock transaction with the specified value" << endl;
  cout << CHANGE << " {new_difficulty} - changes the Blockchain difficulty (i.e. number of necessary 0 in start or end of hash)" << endl;
  cout << SHA << " {num_of_sha} - changes the number of sha256 that will be run for hashing" << endl;
  cout << LOAD << " - loads a blockchain from files/blockchain.json and the transaction list from files/transactions.json" << endl;
  cout << DUMP << " - dumps the current blockchain to files/blockchain.json and the transaction list to files/transactions.json" << endl;
  cout << PRINT << " - prints the current blockchain to cout" << endl;
  cout << QUIT << " - quits the application" << endl;
  cout << HELP << " - prints this help message\n\n" << endl;
}

void CLI::quit() {
  cout << "Quitting safely" << endl;
  running = false;
}

void CLI::run_cmd(string &cmd) {
  if(compare_cmd(cmd, HELP))
    help();
  else if (compare_cmd(cmd, QUIT))
    quit();
  else if (compare_cmd(cmd, CHANGE))
    change();
  else if (compare_cmd(cmd, SHA))
    sha();
  else if (compare_cmd(cmd, LOAD))
    load();
  else if (compare_cmd(cmd, DUMP))
    dump();
  else if (compare_cmd(cmd, PRINT))
    print();
  else if (compare_cmd(cmd, CREATE))
    create();
  else if (compare_cmd(cmd, MINE))
    mine();
  else
    cout << "Command " << cmd << " not found" << endl;
}

bool CLI::compare_cmd(string &cmd, const string &action) {
  to_lower(cmd);
  return cmd.compare(action) == 0;
}
