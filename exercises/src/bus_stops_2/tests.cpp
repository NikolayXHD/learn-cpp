#include <vector>
#include <string>

#include <test_setup.h>

#include "app.cpp"

namespace bus_stops_2 {
  using namespace std;
  void test(const string& in, const string& out) {
    App app;
    ::test_setup::test(app, in, out);
  }

  TEST(bus_stops_2, CASE_1) {
    test(
        "5\n"
        "2 Marushkino Kokoshkino\n"
        "1 Kokoshkino\n"
        "2 Marushkino Kokoshkino\n"
        "2 Kokoshkino Marushkino\n"
        "2 Kokoshkino Kokoshkino",

        "New bus 1\n"
        "New bus 2\n"
        "Already exists for 1\n"
        "Already exists for 1\n"
        "Already exists for 2"
    );
  }
}

