#pragma once

#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "gtest/gtest.h"
#include "app.h"

namespace test_setup {
using namespace std;

void test(App& app, const string& in, const string& out);
}