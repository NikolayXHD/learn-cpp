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

  TEST(bus_stops, CASE_1) {
    test(
        "10\n"
        "ALL_BUSES\n"
        "BUSES_FOR_STOP Marushkino\n"
        "STOPS_FOR_BUS 32K\n"
        "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo\n"
        "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo\n"
        "BUSES_FOR_STOP Vnukovo\n"
        "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo\n"
        "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo\n"
        "STOPS_FOR_BUS 272\n"
        "ALL_BUSES",

        "No buses\n"
        "No stop\n"
        "No bus\n"
        "32 32K\n"
        "Stop Vnukovo: 32 32K 950\n"
        "Stop Moskovsky: no interchange\n"
        "Stop Rumyantsevo: no interchange\n"
        "Stop Troparyovo: 950\n"
        "Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo\n"
        "Bus 32: Tolstopaltsevo Marushkino Vnukovo\n"
        "Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo\n"
        "Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo"
    );
  }
}

