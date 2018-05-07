#pragma once
#include <vector>

class Instance;
class Task;

class Solution {
	int calculatedTimespan = -1;
public:
	std::vector<int> tasks;
	Instance& instance;

	Solution(Instance& instance);

	int calculateTimespan();
	int getCalculatedTimespan();
	void addTask(Task task);

	void print();

	Solution& operator=(const Solution& rhs);
};