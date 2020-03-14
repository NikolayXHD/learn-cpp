#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "gtest/gtest.h"

#include "capital_cities.cpp"

namespace test {
  using namespace std;

  shared_ptr<const string> ensure_trailing_endl(shared_ptr<const string> s) {
    if (s->back() == '\n') {
      return s;
    } else {
      string copy = *s;
      copy += '\n';
      auto result = make_shared<string>(copy);
      return result;
    }
  }

  string normalize(shared_ptr<const string> s) {
    auto copy = ensure_trailing_endl(move(s));
    const auto& is_endl = [](char c) { return c == '\n'; };
    const auto& is_whitespace = [](char c) { return c == ' ' || c == '\n'; };

    stringstream r;
    vector<string> ls;
    boost::split(ls, *copy, is_endl);

    for (auto& l: ls) {
      boost::trim_right_if(l, is_whitespace);
      r << l << endl;
    }
    return r.str();
  }

  void test(const string&& in, const string&& out) {
    stringstream input(in);
    stringstream output;
    ::app2::App app;
    app.run(input, output);
    const string& result = normalize(make_shared<const string>(output.str()));
    const string& out_normalized = normalize(make_shared<const string>(out));
    ASSERT_EQ(result, out_normalized);
  }
}