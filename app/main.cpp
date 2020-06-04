#include <map>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

static auto get_key(const Region& region) {
  return tie(region.std_name, region.parent_std_name, region.population);
}

bool operator<(const Region& r1, const Region& r2) {
  const auto& key1 = get_key(r1);
  const auto& key2 = get_key(r2);

  if (key1 != key2) {
    return key1 < key2;
  }

  return r1.names < r2.names;
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
  if (regions.empty()) {
    return 0;
  }
  map<Region, int> count_by_region;
  for (auto& r : regions) {
    count_by_region[r]++;
  }
  auto max = numeric_limits<int>::min();
  for (auto& [r, count]: count_by_region) {
    if (count > max) {
      max = count;
    }
  }
  return max;
}


int main() {
  cout << FindMaxRepetitionCount(
      {
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89
          },
          {
              "Russia",
              "Eurasia",
              {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
              89
          },
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89
          },
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89
          },
          {
              "Russia",
              "Eurasia",
              {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
              89
          },
      }) << endl;

  cout << FindMaxRepetitionCount(
      {
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
              89
          },
          {
              "Russia",
              "Eurasia",
              {{Lang::DE, "Russland"}, {Lang::FR, "Russie"},      {Lang::IT, "Russia"}},
              89
          },
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
              89
          },
          {
              "Moscow",
              "Toulouse",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
              89
          },
          {
              "Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},      {Lang::IT, "Mosca"}},
              31
          },
      }) << endl;

  return 0;
}