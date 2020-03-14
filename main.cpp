#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>

namespace app {
  using namespace std;

  class App {
  public:
    App() : m_() {}

    void run(basic_istream<char>& in, basic_ostream<char>& out) {
      int count;
      in >> count;

      for (int i = 0; i < count; i++) {
        const auto& m_end = m_.cend();

        string cmd;
        in >> cmd;

        if (cmd == "CHANGE_CAPITAL") {
          string country, capital;
          in >> country >> capital;
          const auto& it = m_.find(country);
          if (it == m_end) {
            out << "Introduce new country " << country << " with capital "
                << capital << endl;
          } else if (it->second == capital) {
            out << "Country " << country << " hasn't changed its capital"
                << endl;
          } else {
            out << "Country " << country << " has changed its capital from "
                << it->second << " to " << capital << endl;
          }
          m_[country] = capital;
        } else if (cmd == "RENAME") {
          string n1, n2;
          in >> n1 >> n2;
          const auto& it = m_.find(n1);
          if (it == m_end || it->first == n2 || m_.find(n2) != m_end) {
            out << "Incorrect rename, skip" << endl;
          } else {
            out << "Country " << n1 << " with capital " << it->second
                << " has been renamed to " << n2 << endl;
            m_[n2] = it->second;
            m_.erase(n1);
          }
        } else if (cmd == "ABOUT") {
          string country;
          in >> country;
          const auto& it = m_.find(country);
          if (it == m_end) {
            out << "Country " << country << " doesn't exist" << endl;
          } else {
            out << "Country " << country << " has capital " << it->second
                << endl;
          }
        } else if (cmd == "DUMP") {
          if (m_.empty()) {
            out << "There are no countries in the world" << endl;
          } else {
            for (const auto& it: m_) {
              out << it.first << '/' << it.second << ' ';
            }
            out << endl;
          }
        } else {
          break;
        }
      }
    }

  private:
    map<string, string> m_;
  };
}


int main() {
  app::App app;
  app.run(std::cin, std::cout);
  return 0;
}