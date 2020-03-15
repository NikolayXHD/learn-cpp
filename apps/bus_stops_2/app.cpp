#include <vector>
#include <string>
#include <iostream>
#include <map>

namespace bus_stops {
using namespace std;

class App {
 public:
  App() : stops_() {}

  void run(basic_istream<char>& in, basic_ostream<char>& out) {
    int count;
    in >> count;

    for (int i = 0; i < count; i++) {
      int stops_count;
      in >> stops_count;
      vector<string> stops(stops_count);
      for (int j = 0; j < stops_count; j++) {
        in >> stops[j];
      }
      auto it = stops_.find(stops);
      if (it == stops_.end()) {
        auto n = stops_.size() + 1;
        stops_[stops] = n;
        out << "New bus " << n << endl;
      } else {
        out << "Already exists for " << it->second << endl;
      }
    }
  }

 private:
  map<vector<string>, int> stops_;
};

}
