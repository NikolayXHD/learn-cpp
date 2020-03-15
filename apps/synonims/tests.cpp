#include <vector>
#include <string>

#include <gtest/gtest.h>
#include <test_setup.h>

#include "app.cpp"

namespace test {
  using namespace std;
  void test(const string& in, const string& out) {
    ::bus_stops::App app;
    ::test_setup::test(app, in, out);
  }

  TEST(synonims, CASE_1) {
    test(
        "8\n"
        "ADD program code\n"
        "COUNT cipher\n"
        "ADD code cipher\n"
        "COUNT code\n"
        "COUNT program\n"
        "CHECK code program\n"
        "CHECK program cipher\n"
        "CHECK cpp java",

        "0\n"
        "2\n"
        "1\n"
        "YES\n"
        "NO\n"
        "NO"
    );
  }
}

