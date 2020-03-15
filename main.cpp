#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>

namespace app {
using namespace std;

class App {
 public:
  App() : map_() {}

  void run(basic_istream<char>& cin, basic_ostream<char>& cout) {
    int count;
    cin >> count;

    for (int i = 0; i < count; i++) {
      string cmd;
      cin >> cmd;
      if (cmd == "ADD") {
        string w1, w2;
        cin >> w1 >> w2;
        map_[w1].insert(w2);
        map_[w2].insert(w1);
      } else if (cmd == "COUNT") {
        string w;
        cin >> w;
        cout << map_[w].size() << endl;
      } else if (cmd == "CHECK") {
        string w1, w2;
        cin >> w1 >> w2;
        if (map_[w1].count(w2) > 0) {
          cout << "YES";
        } else {
          cout << "NO";
        }
        cout << endl;
      }
    }
  }

 private:
  map<string, set<string>> map_;
};
}

int main() {
  app::App app;
  app.run(std::cin, std::cout);
  return 0;
}
