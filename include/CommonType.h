#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <random>

namespace ZTE_crb {
    enum class VexType : int{ START, END, COMMON, MUST, FORBID };
    enum class EdgeType : int{ COMMON, MUST, FORBID };

    using Vex = int;
    using Path = std::vector<Vex>;
    using Edge = std::pair<Vex, Vex>;
    using Matrix = std::vector<Path>;

    const int MAX_VEX = INT_MAX;
    const int MAX_EDGE = INT_MAX;
    const int MAX_DIS = INT_MAX;

    const int FORBID_VEX_VALUE = 5000;
    const int FORBID_EDGE_VALUE = 5000;
    const int MUST_VEX_VALUE = 500;
    const int MUST_EDGE_VALUE = 500;
    const int OVER_VEX_VALUE = 1000;
}