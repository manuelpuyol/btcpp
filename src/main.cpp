#include<cli.hpp>
#include<json.hpp>

#ifdef USE_CUDA
#include<cmine.hpp>
#endif

int main() {
#ifdef USE_CUDA
  string test = "4b0acdb5cbae48a37b9b8b9c95ec2e64ef47fffa9adbfe2d8fed6e139e05ae35";
  tuple<int, uint32_t> result = cmine(test, 5);

  if(get<0>(result) == FOUND) {
    uint32_t nonce = get<1>(result);
    string str = test + to_string(nonce);
    string hash = btc_hash(str);

    cout << "nonce = " << nonce << endl;
    cout << "hash = " << hash << endl;
  }
#else
  CLI cli;

  cli.run();
#endif
}
