#include "stdafx.h"
#include "Reader.h"
#include <fstream>
#include <string>

using namespace std;

Instance Reader::loadInstance(int problemSize, int param, int instance) {
	string path = "./Data/" + to_string(problemSize) + "/";
	switch (problemSize) {
	case 30:
		return loadInstance(path+"J" + to_string(problemSize) + to_string(param) + "_" + to_string(instance) + ".RCP");
		break;
	case 120:
		return loadInstance(path+"X" + to_string(param) + "_" + to_string(instance) + ".RCP");
		break;
	}
	
}

Instance Reader::loadInstance(string path)
{
	ifstream file;
	file.open(path);
	if (!file.is_open()) {
		cout << "File not found" << endl;
		return Instance();
	}
	Instance instance;
	int taskCount;
	int resourceCount;

	instance.id = path;
	file >> taskCount >> resourceCount;
	instance.resources.resize(resourceCount);
	for (int i = 0; i < resourceCount; ++i) {
		file >> instance.resources[i];
	}
	// duration, task requirements, 
	// number of succesors, succesors
	for (int i = 0; i < taskCount; ++i) {
		Task task;
		task.id = i;
		int successorCount;
		file >> task.time;
		task.resources.resize(resourceCount);
		for (int j = 0; j < resourceCount; ++j) {
			file >> task.resources[j];
		}
		file >> successorCount;
		task.successors.resize(successorCount);
		for (int j = 0; j < successorCount; ++j) {
			file >> task.successors[j];
			task.successors[j]--;
		}
		instance.tasks.push_back(task);
	}
	for (Task task : instance.tasks) {
		for (int successor : task.successors) {
			instance.tasks[successor].predecessors.push_back(task.id);
		}
	}
	return instance;
}
