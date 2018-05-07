#include "stdafx.h"
#include "Solution.h"
#include "SerialScheduleGenerator.h"
#include <assert.h>
#include <algorithm>

using namespace std;


Solution::Solution(Instance& instance) : instance(instance)
{
}

int Solution::calculateTimespan()
{
	if (tasks[0] != 0) {
		cout << "First task is not task 0!" << endl;
		return -1;
	}
	if (tasks[tasks.size() - 1] != tasks.size() - 1) {
		cout << "Final task is not task with highest id!" << endl;
		return -1;
	}
	vector<vector<int>> freeResources; // [time][resource]
	vector<int> earliestStartTimes(instance.tasks.size());
	SerialScheduleGenerator serialScheduleGenerator(instance);
	
	for (int i = 0; i < tasks.size(); i++) {
		int taskId = tasks[i];
		Task task = instance.tasks[taskId];
		if (!serialScheduleGenerator.isTaskAvailable(task)) {
			cout << "Task " << taskId << " was scheduled before it's predecessors!" << endl;
			return -1;
		}
		int earliestPossibleTime = earliestStartTimes[taskId];
		int counter = 0;
		while (counter != task.time) {
			int t = counter + earliestPossibleTime;
			assert(t <= freeResources.size() + 1);
			if (t >= freeResources.size()) {
				freeResources.push_back(vector<int>(instance.resources));
				counter++;
			} else {
				bool enoughResources = true;
				for (int j = 0; j < task.resources.size(); j++) {
					if (task.resources[j] > freeResources[t][j]) {
						enoughResources = false;
						break;
					}
				}
				if (enoughResources) {
					counter++;
				} else {
					counter = 0;
					earliestPossibleTime = t + 1;
				}
			}
		}
		
		if (taskId == tasks.size() - 1) {
			// if this is the last task -> return result
			calculatedTimespan = earliestPossibleTime;
			return earliestPossibleTime;
		} else {
			// otherwise add task to schedule
			serialScheduleGenerator.addTask(task);
			for (int succesor : task.successors) {
				int timeForSuccessor = earliestPossibleTime + task.time;
				if (timeForSuccessor > earliestStartTimes[succesor]) {
					earliestStartTimes[succesor] = timeForSuccessor;
				}
			}
			//availableTasks.insert(task.successors.begin(), task.successors.end());
			for (int i = earliestPossibleTime; i < earliestPossibleTime + task.time; i++) {
				for (int j = 0; j < task.resources.size(); j++) {
					freeResources[i][j] -= task.resources[j];
				}
			}
		}
	}
	return 0;
}

int Solution::getCalculatedTimespan() {
	if (calculatedTimespan == -1) {
		cout << "ERROR: Retrieving uninitialized calculated timespan" << endl;
	}
	return calculatedTimespan;
}

void Solution::addTask(Task task)
{
	tasks.push_back(task.id);
}


void Solution::print()
{
	cout << "Solution score: " << calculateTimespan() << endl;
	cout << "Tasks: ";
	for (Task task : instance.tasks) {
		cout << task.id;
	}
	cout << endl;
}

Solution & Solution::operator=(const Solution & rhs) {
	if (instance.id != rhs.instance.id) {
		cout << "ERROR: Assigning solution with different instance id!" << endl;
		cout << "lhs: " << instance.id << endl;
		cout << "rhs: " << rhs.instance.id << endl;
	}
	calculatedTimespan = rhs.calculatedTimespan;
	tasks = rhs.tasks;
	return *this;
}
