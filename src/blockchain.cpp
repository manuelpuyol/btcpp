#include<blockchain.hpp>

Blockchain::Blockchain(unsigned int _difficulty) : difficulty(_difficulty), nblocks(1) {
  add_initial_mock_block();
}

Blockchain::Blockchain(vector<Block> &&_blocks, unsigned int _difficulty) :
  blocks(move(_blocks)),
  difficulty(_difficulty) {
  nblocks = blocks.size();
}

Blockchain::Blockchain(const ptree &json) :
  difficulty(json.get<unsigned int>("difficulty")),
  nblocks(json.get<unsigned int>("nblocks")) {
  for(auto &element: json.get_child("blocks"))
    blocks.push_back(element.second);
}

void Blockchain::add_block(vector<Transaction> &&transactions, unsigned long nonce, string root, string hash) {
  Header header(nonce, last_hash(), root);

  if(hash.compare(header.hash) != 0) {
    cout << "Invalid block!" << endl;
    return;
  }

  Block block(move(header), move(transactions));

  blocks.push_back(move(block));
  nblocks++;
}

void Blockchain::add_initial_mock_block() {
  Header h(0, "", sha256("mock"));
  Block b(move(h));

  blocks.push_back(b);
}

string Blockchain::last_hash() {
  return blocks.back().header.hash;
}

ptree Blockchain::to_json() const {
  ptree json;
  ptree jblocks;

  for (auto &block : blocks)
    jblocks.push_back(std::make_pair("", block.to_json()));

  json.put("nblocks", nblocks);
  json.put("difficulty", difficulty);
  json.add_child("blocks", jblocks);

  return json;
}

ostream &operator<<(ostream &os, const Blockchain &bc) {
  write_json(os, bc.to_json());

  return os;
}
