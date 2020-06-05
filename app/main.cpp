#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

template<typename TKey, typename TValue>
TValue& GetRefStrict(map<TKey, TValue>& m, const TKey& key) {
  const auto& it = m.find(key);
  if (it == m.cend()) {
    throw runtime_error("not found");
  }
  TValue& result = it->second;
  return result;
}

int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
}