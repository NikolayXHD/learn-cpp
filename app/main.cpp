#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace app {

class App {
 public:
  App() = default;

  static void run(basic_istream<char>& cin, basic_ostream<char>& cout) {
    int n;
    cin >> n;
    std::vector<int32_t> t(n);
    int64_t s = 0;
    for (int i = 0; i < n; i++) {
      int32_t& ti = t[i];
      cin >> ti;
      s += ti;
    }

    vector<int> h;
    for (int i = 0; i < n; i++) {
      if (static_cast<int64_t>(t[i]) * n > s)
      h.push_back(i);
    }

    cout << h.size() << std::endl;
    for (const auto& v: h) {
      cout << v << ' ';
    }
    cout << std::endl;
  }
};
}

int main() {
  app::App::run(std::cin, std::cout);
  return 0;
}
