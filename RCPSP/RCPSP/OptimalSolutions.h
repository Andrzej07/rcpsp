#pragma once
#include <map>
#include <string>

class OptimalSolutions {
	std::map<std::string, int> makespans;
public:
	OptimalSolutions(int problemSize);

	int getOptimalTimespan(int param, int instance);
};