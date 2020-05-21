#include<cli.hpp>
#include<json.hpp>

int main() {
  // CLI cli;

  // cli.run();

  Transaction t(10);
  write_json(cout, to_json(t));
}
