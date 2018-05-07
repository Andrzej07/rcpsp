#pragma once
#include <vector>

class Task {
public:
	int id;
	int time;
	std::vector<int> resources;
	std::vector<int> successors;
	std::vector<int> predecessors;

	void print();
};