#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <app.h>

using namespace std;

namespace bus_stops {

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type = QueryType::NewBus;
  string bus;
  string stop;
  vector<string> stops;
};

const vector<string> empty_list{};
const vector<pair<string, vector<string>>> empty_list_list{};

istream& operator>>(istream& is, Query& q);

struct BusesForStopResponse {
  const vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  const string bus;
  const vector<pair<string, vector<string>>> buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r);

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops);

  [[nodiscard]] BusesForStopResponse GetBusesForStop(const string& stop) const;

  [[nodiscard]] StopsForBusResponse GetStopsForBus(const string& bus) const;

  [[nodiscard]] AllBusesResponse GetAllBuses() const;

 private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

class App : public ::test_setup::App {
  void run(basic_istream<char>& in, basic_ostream<char>& out) override;
};

}
