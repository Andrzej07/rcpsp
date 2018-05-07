#include "stdafx.h"

using namespace std;

void Task::print()
{
	cout << "***" << endl;
	cout << "Task id: " << id << " Time: " << time << endl;
	cout << "Recources: ";
	for (int resource : resources) {
		cout << resource << " ";
	}
	cout << endl;
	cout << "Successors: ";
	if (successors.size() == 0) {
		cout << "None";
	}
	for (int successor : successors) {
		cout << successor << " ";
	}
	cout << endl;
	cout << "Predecessors: ";
	if (predecessors.size() == 0) {
		cout << "None";
	}
	for (int predecessor : predecessors) {
		cout << predecessor << " ";
	}
	cout << endl;
}
