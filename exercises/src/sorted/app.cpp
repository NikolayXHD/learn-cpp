#include <string>
#include <vector>
#include <map>

using namespace std;

namespace sorted {

class SortedStrings {
 public:
  void AddString(const string& s) {
    v_[s]++;
    count_++;
  }
  vector<string> GetSortedStrings() {
    vector<string> r;
    for (const auto& [value, count]: v_) {
      for (int i = 0; i < count; i++) {
        r.push_back(value);
      }
    }
    return r;
  }
 private:
  map<string, int> v_;
  int count_;
};

}
