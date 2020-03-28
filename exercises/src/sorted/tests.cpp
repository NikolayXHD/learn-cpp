#include "gtest/gtest.h"

#include "app.cpp"

namespace sorted {
using namespace std;

TEST(sorted, CASE_1) {
  SortedStrings s;
  s.AddString("b");
  s.AddString("a");
  s.AddString("b");
  auto r = s.GetSortedStrings();
  ASSERT_EQ(r.size(), 3);
  ASSERT_EQ(r[0], "a");
  ASSERT_EQ(r[1], "b");
  ASSERT_EQ(r[1], "b");
}
}


