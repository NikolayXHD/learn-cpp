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
  App() {}

  void run(basic_istream<char>& cin, basic_ostream<char>& cout) {
    int count;
    cin >> count;
    vector<pair<string, string>> values(count);
    for (auto& [v, v_lower]: values) {
      cin >> v;
      v_lower = v;
      transform(v_lower.begin(), v_lower.end(), v_lower.begin(),
                [](char c) { return tolower(c); });
    }
    sort(values.begin(), values.end(),
         [](const auto& pair1, const auto& pair2) {
           return pair1.second < pair2.second;
         });
    for (const auto& [v, v_lower]: values) {
      cout << v << ' ';
    }
    cout << endl;
  }
};
}

int main() {
  app::App app;
  app.run(std::cin, std::cout);
  return 0;
}
