#pragma once

class Instance;
class Solution;

class Algorithm {
protected:
	Instance& instance;

public:
	Algorithm(Instance& instance);

	virtual Solution solve(int) = 0;
};