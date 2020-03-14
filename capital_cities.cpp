#include "gtest/gtest.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

namespace app2 {
  map<string, string> m;

  void process_commands(basic_istream<char>& in, basic_ostream<char>& out) {
    int count;
    in >> count;

    for (int i = 0; i < count; i++) {
      const auto& m_end = m.cend();

      string cmd;
      in >> cmd;

      if (cmd == "CHANGE_CAPITAL") {
        string country, capital;
        in >> country >> capital;
        const auto& it = m.find(country);
        if (it == m_end) {
          out << "Introduce new country " << country << " with capital "
              << capital << endl;
        } else if (it->second == capital) {
          out << "Country " << country << " hasn't changed its capital" << endl;
        } else {
          out << "Country " << country << " has changed its capital from "
              << it->second << " to " << capital << endl;
        }
        m[country] = capital;
      } else if (cmd == "RENAME") {
        string n1, n2;
        in >> n1 >> n2;
        const auto& it = m.find(n1);
        if (it == m_end || it->first == n2 || m.find(n2) != m_end) {
          out << "Incorrect rename, skip" << endl;
        } else {
          out << "Country " << n1 << " with capital " << it->second
              << " has been renamed to " << n2 << endl;
          m[n2] = it->second;
          m.erase(n1);
        }
      } else if (cmd == "ABOUT") {
        string country;
        in >> country;
        const auto& it = m.find(country);
        if (it == m_end) {
          out << "Country " << country << " doesn't exist" << endl;
        } else {
          out << "Country " << country << " has capital " << it->second << endl;
        }
      } else if (cmd == "DUMP") {
        if (m.empty()) {
          out << "There are no countries in the world" << endl;
        } else {
          for (const auto& it: m) {
            out << it.first << '/' << it.second << ' ';
          }
          out << endl;
        }
      } else {
        break;
      }
    }
  }
}

namespace test {
  void assert_equal(const string& s1, const string& s2) {
    vector<string> ls1;
    vector<string> ls2;
    const auto& is_line_end = [](char c) { return c == '\n'; };
    const auto& is_whitespace = [](char c) { return c == ' ' || c == '\n'; };
    boost::split(ls1, s1, is_line_end);
    boost::split(ls2, s2, is_line_end);

    ASSERT_EQ(ls1.size(), ls2.size());

    for (int i = 0; i < ls1.size(); i++) {
      string l1 = ls1[i];
      string l2 = ls2[i];
      boost::trim_right_if(l1, is_whitespace);
      boost::trim_right_if(l2, is_whitespace);

      EXPECT_EQ(l1, l2);
    }
  }

  void test(const string& in, const string& out) {
    stringstream input(in);
    stringstream output;
    ::app2::process_commands(input, output);
    const auto& result = output.str();
    assert_equal(result, out);
  }

  TEST(SUITE, CASE_1) {
    test(
        "6\n"
        "CHANGE_CAPITAL RussianEmpire Petrograd\n"
        "RENAME RussianEmpire RussianRepublic\n"
        "ABOUT RussianRepublic\n"
        "RENAME RussianRepublic USSR\n"
        "CHANGE_CAPITAL USSR Moscow\n"
        "DUMP\n",

        "Introduce new country RussianEmpire with capital Petrograd\n"
        "Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic\n"
        "Country RussianRepublic has capital Petrograd\n"
        "Country RussianRepublic with capital Petrograd has been renamed to USSR\n"
        "Country USSR has changed its capital from Petrograd to Moscow\n"
        "USSR/Moscow asd\n"
    );
  }
}

