#pragma once
#include <vector>
#include <set>
#include "Solution.h"

class Task;
class Instance;

class SerialScheduleGenerator {
	Instance& instance;
	Solution solution;
	std::vector<std::vector<int>> predecessors;
	std::set<int> availableTasks;
public:

	SerialScheduleGenerator(Instance& instance);

	void addTask(Task& task);
	bool isTaskAvailable(Task& task);
	bool isFinished();
	int getNumberOfScheduledTasks();
	const std::set<int>& getAvailableTasks();
	Solution getSolution();
};