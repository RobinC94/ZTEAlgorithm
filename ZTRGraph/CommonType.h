#pragma once
#include <vector>

namespace ZTE_crb {
	enum class VexType : int{ START, END, COMMON, MUST, FORBIT };
	enum class EdgeType : int { COMMON, MUST, FORBIT };
	
	using Vex = int;
	using Path = std::vector<Vex>;
	using Edge = std::pair<Vex, Vex>;
	using Matrix = std::vector<Path>;

	const int MAX_VEX = INT_MAX;
	const int MAX_EDGE = INT_MAX;
	const int MAX_DIS = INT_MAX;
}