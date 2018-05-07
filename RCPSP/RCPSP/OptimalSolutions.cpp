#include "stdafx.h"
#include "OptimalSolutions.h"
#include <fstream>

using namespace std;

string createKey(int param, int instance) {
	return to_string(param) + "_" + to_string(instance);
}

OptimalSolutions::OptimalSolutions(int problemSize) {
	ifstream file;
	string path = "./Data/opt/j" + to_string(problemSize) + ".opt";
	file.open(path);
	if (!file.is_open()) {
		cout << "File " << path << " not found" << endl;
		return;
	}
	while (!file.eof()) {
		int param, instance, makespan;
		float time;
		file >> param >> instance >> makespan >> time;
		makespans.insert(pair<string, int>(createKey(param, instance), makespan));
	}
}

int OptimalSolutions::getOptimalTimespan(int param, int instance) {
	map<string, int>::iterator it = makespans.find(createKey(param, instance));
	if (it != makespans.end()) {
		return it->second;
	}
	return -1;
}
