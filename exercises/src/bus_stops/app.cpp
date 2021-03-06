#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "app.h"

using namespace std;

namespace bus_stops {

istream& operator>>(istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  q.stops.clear();
  q.bus.clear();
  q.stop.clear();
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.reserve(stop_count);
    for (int i = 0; i < stop_count; i++) {
      string stop;
      is >> stop;
      q.stops.push_back(stop);
    }
  } else if (operation_code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (operation_code == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop";
  } else {
    for (const string& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
  if (r.bus.empty()) {
    os << "No bus";
    return os;
  }

  bool non_first = false;
  for (const auto&[stop, buses] : r.buses) {
    if (non_first) {
      os << endl;
    } else {
      non_first = true;
    }
    os << "Stop " << stop << ": ";
    if (buses.size() == 1) {
      os << "no interchange";
      continue;
    }

    for (const string& other_bus : buses) {
      if (r.bus != other_bus) {
        os << other_bus << " ";
      }
    }
  }

  return os;
}

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
    return os;
  }

  bool non_first = false;
  for (const auto& bus_item : r.buses_to_stops) {
    if (non_first) {
      os << endl;
    } else {
      non_first = true;
    }
    os << "Bus " << bus_item.first << ": ";
    for (const string& stop : bus_item.second) {
      os << stop << " ";
    }
  }

  return os;
}

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops[bus] = stops;
  for (const string& stop : stops) {
    stops_to_buses[stop].push_back(bus);
  }
}

[[nodiscard]] BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  const auto& it = stops_to_buses.find(stop);
  if (it == stops_to_buses.cend())
    return {empty_list};
  return {it->second};
}

[[nodiscard]] StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  const auto& it = buses_to_stops.find(bus);
  if (it == buses_to_stops.cend()) {
    return {"", empty_list_list};
  }
  const vector<string>& stops = it->second;

  vector<pair<string, vector<string>>> changes;
  changes.reserve(stops.size());
  for (const auto& stop : stops) {
    changes.emplace_back(stop, stops_to_buses.at(stop));
  }
  return {bus, changes};
}

[[nodiscard]] AllBusesResponse BusManager::GetAllBuses() const {
  return {buses_to_stops};
}

void App::run(basic_istream<char>& in, basic_ostream<char>& out) {
  int query_count;
  Query q;

  in >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    in >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        out << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        out << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        out << bm.GetAllBuses() << endl;
        break;
    }
  }
}
}
