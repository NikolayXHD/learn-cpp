#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

namespace app {

class App {
 public:
  App() = default;

  static void run(basic_istream<char>& cin, basic_ostream<char>& cout) {
    int n, r;
    int x, y, z;
    cin >> n >> r;

    uint64_t s = 0;
    for (int i = 0; i < n; i++) {
      cin >> x >> y >> z;
      s += static_cast<int64_t>(x) * y * z;
    }

    s *= r;

    cout << s << std::endl;
  }
};
}

int main() {
  app::App::run(std::cin, std::cout);
  return 0;
}
