#include <string>
#include <iostream>
#include <map>
#include <set>

#include <app.h>

namespace bus_stops_2 {
using namespace std;

class App: public ::test_setup::App {
 public:
  App() : stops_() {}

  void run(basic_istream<char>& in, basic_ostream<char>& out) override {
    int count;
    in >> count;

    for (int i = 0; i < count; ++i) {
      int stops_count;
      in >> stops_count;
      set<string> stops;
      for (int j = 0; j < stops_count; ++j) {
        string stop;
        in >> stop;
        stops.insert(stop);
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
  map<set<string>, int> stops_;
};

}
