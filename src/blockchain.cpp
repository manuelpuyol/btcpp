#include<blockchain.hpp>

Blockchain::Blockchain(unsigned int _difficulty) : difficulty(_difficulty), nblocks(0) {}

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

void Blockchain::add_block(vector<Transaction> &&transactions, uint32_t nonce, string root, string hash, int number_of_sha) {
  Header header(nonce, last_hash(), root, number_of_sha);
  header.hash = hash;

  if(!header.is_valid()) {
    cout << "Invalid block!" << endl;
    return;
  }

  Block block(move(header), move(transactions));

  blocks.push_back(move(block));
  nblocks++;
}

string Blockchain::last_hash() {
  if(nblocks == 0)
    return "";

  return blocks.back().header.hash;
}

blockchain_map Blockchain::get_map() const {
  blockchain_map m;

  m["blocks"] = blocks;
  m["nblocks"] = nblocks;
  m["difficulty"] = difficulty;

  return m;
}

bool Blockchain::is_valid() {
  Hash hash(difficulty);
  string last_hash = "";

  for(auto &b: blocks) {
    hash.set_h(b.header.hash);

    if(
      b.header.prev_hash.compare(last_hash) != 0 ||
      !hash.is_valid() ||
      !b.is_valid()
    )
      return false;

    last_hash = b.header.hash;
  }

  return true;
}

ostream &operator<<(ostream &os, const Blockchain &bc) {
  write_json(os, to_json(bc));

  return os;
}
