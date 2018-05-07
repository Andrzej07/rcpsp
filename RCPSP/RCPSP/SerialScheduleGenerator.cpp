#include "stdafx.h"
#include "SerialScheduleGenerator.h"
#include <vector>
#include <algorithm>

using namespace std;

SerialScheduleGenerator::SerialScheduleGenerator(Instance& instance): instance(instance), solution(instance) {
	for (Task& task : instance.tasks) {
		predecessors.push_back(vector<int>(task.predecessors));
	}
	availableTasks.insert(0);
}

void SerialScheduleGenerator::addTask(Task& task) {
	if (availableTasks.find(task.id) == availableTasks.end()) {
		cout << "Adding unavailable task with id: " << task.id << endl;
	}
	availableTasks.erase(task.id);
	for (int successor : task.successors) {
		auto& tmp = predecessors[successor];
		tmp.erase(remove(tmp.begin(), tmp.end(), task.id), tmp.end());
		if (tmp.size() == 0) {
			availableTasks.insert(successor);
		}
	}
	solution.tasks.push_back(task.id);
}

bool SerialScheduleGenerator::isTaskAvailable(Task& task) {
	return availableTasks.find(task.id) != availableTasks.end();
}

bool SerialScheduleGenerator::isFinished() {
	return solution.tasks.size() == instance.tasks.size();
}

int SerialScheduleGenerator::getNumberOfScheduledTasks() {
	return static_cast<int>(solution.tasks.size());
}

const std::set<int>& SerialScheduleGenerator::getAvailableTasks() {
	return availableTasks;
}

Solution SerialScheduleGenerator::getSolution() {
	if (solution.tasks.size() != instance.tasks.size()) {
		cout << "Returning an incomplete solution!" << endl;
	}
	return solution;
}




