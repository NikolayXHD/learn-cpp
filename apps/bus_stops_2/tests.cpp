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

  TEST(bus_stops_2, CASE_1) {
    test(
        "4\n"
        "2 Marushkino Kokoshkino\n"
        "1 Kokoshkino\n"
        "2 Marushkino Kokoshkino\n"
        "2 Kokoshkino Marushkino",

        "New bus 1\n"
        "New bus 2\n"
        "Already exists for 1\n"
        "New bus 3"
    );
  }
}

