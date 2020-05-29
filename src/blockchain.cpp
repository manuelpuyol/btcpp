#include<blockchain.hpp>

Blockchain::Blockchain(unsigned int _difficulty) : difficulty(_difficulty), nblocks(1) {
  add_initial_mock_block();
  members_map = generate_map(*this);
}

Blockchain::Blockchain(vector<Block> &&_blocks, unsigned int _difficulty) :
  blocks(move(_blocks)),
  difficulty(_difficulty) {
  nblocks = blocks.size();
  members_map = generate_map(*this);
}

Blockchain::Blockchain(const ptree &json) :
  difficulty(json.get<unsigned int>("difficulty")),
  nblocks(json.get<unsigned int>("nblocks")) {
  for(auto &element: json.get_child("blocks"))
    blocks.push_back(element.second);
  members_map = generate_map(*this);
}

void Blockchain::add_block(vector<Transaction> &&transactions, unsigned long nonce, string root, string hash, int number_of_sha) {
  Header header(nonce, last_hash(), root,number_of_sha);

  if(hash.compare(header.hash) != 0) {
    cout << "Invalid block!" << endl;
    return;
  }

  Block block(move(header), move(transactions));

  blocks.push_back(move(block));
  nblocks++;
}

void Blockchain::add_initial_mock_block() {
  Header h(0, "", sha256("mock"), 2);
  Block b(move(h));

  blocks.push_back(b);
}

string Blockchain::last_hash() {
  return blocks.back().header.hash;
}

blockchain_map Blockchain::get_map() const {
  return members_map;
}

ostream &operator<<(ostream &os, const Blockchain &bc) {
  write_json(os, to_json(bc));

  return os;
}

blockchain_map generate_map(Blockchain &bc) {
  blockchain_map m;

  m["blocks"] = bc.blocks;
  m["nblocks"] = bc.nblocks;
  m["difficulty"] = bc.difficulty;

  return m;
}
