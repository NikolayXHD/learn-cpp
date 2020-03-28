#pragma once

#include <istream>
#include <ostream>

namespace test_setup {
using namespace std;

class App {
 public:
  virtual void run(basic_istream<char>& in, basic_ostream<char>& out) {}
};

}
