#include<cli.hpp>
#include<json.hpp>

int main() {
  CLI cli;

  cli.run();
}

void test_json() {
  Transaction t(10);
  write_json(cout, to_json(t));

  Header h(10, "123" , "456");
  write_json(cout, to_json(h));

  vector<Transaction> v;
  v.push_back(t);

  Block b(move(h), move(v));
  write_json(cout, to_json(b));

  vector<Block> vv;
  vv.push_back(b);

  Blockchain bc(move(vv), 1);
  write_json(cout, to_json(bc));
}
