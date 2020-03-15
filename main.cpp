#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <set>

namespace app {
using namespace std;

class App {
 public:
  App() : values_() {}

  void run(basic_istream<char>& in, basic_ostream<char>& out) {
    int count;
    in >> count;

    for (int i = 0; i < count; i++) {
      string v;
      in >> v;
      values_.insert(v);
    }

    out << values_.size() << endl;
  }

 private:
  set<string> values_;
};
}


//int main() {
//  app::App app;
//  app.run(std::cin, std::cout);
//  return 0;
//}