#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

namespace bus_stops {
using namespace std;

class App {
 public:
  App() : stops_(), buses_() {}

  void run(basic_istream<char>& in, basic_ostream<char>& out) {
    int count;
    in >> count;

    for (int i = 0; i < count; i++) {
      string cmd;
      in >> cmd;
      if (cmd == "NEW_BUS") {
        string bus_name;
        int stops_count;
        in >> bus_name >> stops_count;

        auto& stops = stops_[bus_name];
        for (int j = 0; j < stops_count; j++) {
          string stop_name;
          in >> stop_name;
          stops.push_back(stop_name);
          buses_[stop_name].push_back(bus_name);
        }
      } else if (cmd == "BUSES_FOR_STOP") {
        string stop_name;
        in >> stop_name;
        const vector<string>& buses = buses_[stop_name];
        if (buses.empty()) {
          out << "No stop" << endl;
        } else {
          for (const auto& bus_name: buses) {
            out << bus_name << ' ';
          }
          out << endl;
        }
      } else if (cmd == "STOPS_FOR_BUS") {
        string bus_name;
        in >> bus_name;
        const vector<string>& stops = stops_[bus_name];
        if (stops.empty()) {
          out << "No bus" << endl;
        } else {
          for (const auto& stop_name: stops) {
            out << "Stop " << stop_name << ": ";
            stringstream stop_descr;
            for (const auto& b_name: buses_[stop_name]) {
              if (b_name != bus_name) {
                stop_descr << b_name << ' ';
              }
            }
            if (stop_descr.str().empty()) {
              stop_descr << "no interchange";
            }
            out << stop_descr.str() << endl;
          }
        }
      } else if (cmd == "ALL_BUSES") {
        if (stops_.empty()) {
          out << "No buses" << endl;
        } else {
          for (const auto&[bus_name, stops]: stops_) {
            out << "Bus " << bus_name << ": ";
            for (const auto& stop_name: stops) {
              out << stop_name << ' ';
            }
            out << endl;
          }
        }
      } else {
        break;
      }
    }
  }

 private:
  map<string, vector<string>> stops_;
  map<string, vector<string>> buses_;
};

}
