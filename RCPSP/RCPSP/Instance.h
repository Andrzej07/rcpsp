#pragma once
#include <vector>
#include <string>
#include "Task.h"

class Instance {
public:
	std::vector<Task> tasks;
	std::vector<int> resources;
	std::string id;

	int getNumberOfTasks();
	int getNumberOfResources();

	void print();
};