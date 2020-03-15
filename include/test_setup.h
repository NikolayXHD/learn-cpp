#pragma once

#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "gtest/gtest.h"

namespace test_setup {
  using namespace std;

  string ensure_trailing_endl(string s) {
    if (s.back() != '\n') {
      s.push_back('\n');
    }
    return s;
  }

  bool is_endl(char c) {
    return c == '\n';
  }

  bool is_whitespace(char c) {
    return c == ' ' || c == '\n';
  }

  string normalize(const string& s) {
    auto copy = ensure_trailing_endl(s);
    stringstream result;
    vector<string> ls;
    boost::split(ls, copy, is_endl);
    for (auto& l: ls) {
      boost::trim_right_if(l, is_whitespace);
      result << l << endl;
    }
    return result.str();
  }

  template<typename TApp>
  void test(TApp& app, const string& in, const string& out) {
    stringstream input(in);
    stringstream output;
    app.run(input, output);
    const string& result = normalize(output.str());
    const string& out_normalized = normalize(out);
    ASSERT_EQ(result, out_normalized);
  }
}