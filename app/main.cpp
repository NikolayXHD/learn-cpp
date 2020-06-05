#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

template<typename TKey, typename TValue>
TValue Sqr(const TValue& original);

template<typename TKey, typename TValue>
map<TKey, TValue> Sqr(const map<TKey, TValue>& original);

template<typename TValue>
vector<TValue> Sqr(const vector<TValue>& original);



template<typename TKey, typename TValue>
pair<TKey, TValue> operator*(pair<TKey, TValue> p1, pair<TKey, TValue> p2) {
  return pair<TKey, TValue>(
      p1.first * p2.first, p1.second * p2.second
  );
}

template<typename TValue>
TValue Sqr(const TValue& original) {
  return original * original;
}

template<typename TKey, typename TValue>
map<TKey, TValue> Sqr(const map<TKey, TValue>& original) {
  map<TKey, TValue> result;
  for (const auto& [key, value]: original) {
    result[key] = Sqr(value);
  }
  return result;
}

template<typename TValue>
vector<TValue> Sqr(const vector<TValue>& original) {
  vector<TValue> result;
  result.reserve(original.size());
  for (const auto& value: original) {
    result.push_back(Sqr(value));
  }
  return result;
}


int main() {
  // Пример вызова функции
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
  return 0;
}