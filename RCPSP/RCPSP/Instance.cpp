#include "stdafx.h"

using namespace std;

int Instance::getNumberOfTasks()
{
	return tasks.size();
}

int Instance::getNumberOfResources()
{
	return resources.size();
}

void Instance::print()
{
	cout << "Number of resources: " << getNumberOfResources() << endl;
	cout << "Resources: ";
	for (int resource : resources) {
		cout << resource << " ";
	}
	cout << endl;
	cout << "Tasks: " << getNumberOfTasks() << endl;
	for (Task task : tasks) {
		task.print();
	}
}
