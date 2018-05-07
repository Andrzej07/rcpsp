#include "stdafx.h"
#include "ACOAlgorithm.h"
#include "Solution.h"
#include "GPRWHeuristic.h"
#include "SerialScheduleGenerator.h"
#include <cmath>

using namespace std;

Solution ACOAlgorithm::solve(int optimalMakespan) {
	cout << "***" << endl << "ACO Start" << endl;
	Solution bestSolution(instance);
	int bestTimespan = INT_MAX;
	Heuristic* heuristic;
	GPRWHeuristic gprwh(instance.tasks);
	heuristic = &gprwh;
	initializePheromones();
	for (int gen = 0; gen < 25; gen++) {
		Solution bestGenSolution(instance);
		int bestGenTimespan = INT_MAX;
		cout << "Generation: " << gen+1 << endl;
		for (int ant = 0; ant < ants; ant++) {
			SerialScheduleGenerator ssg(instance);
			while (!ssg.isFinished()) {
				Task& selected = selectTask(ssg, heuristic);
				ssg.addTask(selected);
			}
			Solution sol = ssg.getSolution();
			if (bestGenTimespan > sol.calculateTimespan()) {
				if (sol.getCalculatedTimespan() == optimalMakespan) {
					cout << "Ant " << ant + 1 << " found optimal solution: " << sol.getCalculatedTimespan() << endl;
					cout << "ACO End" << endl << "***" << endl;
					return sol;
				}
				bestGenSolution = sol;
				bestGenTimespan = sol.getCalculatedTimespan();
				
			}
		}
		// evaporation
		for (int i = 0; i < pheromones.size(); i++) {
			for (int j = 0; j < pheromones[i].size(); j++) {
				pheromones[i][j] *= evaporationRate;
				if (pheromones[i][j] < minPhero) {
					pheromones[i][j] = minPhero;
				}
			}
		}
		if (bestTimespan > bestGenTimespan) {
			cout << "Improving best solution: " << bestGenSolution.getCalculatedTimespan() << endl;
			bestSolution = bestGenSolution;
			bestTimespan = bestGenTimespan;
		}
		// leave trail
		float ratio = bestTimespan / (float)bestGenTimespan;
		for (int i = 0; i < bestSolution.tasks.size(); i++) {
			pheromones[i][bestSolution.tasks[i]] += ratio;
		}
		for (int i = 0; i < bestSolution.tasks.size(); i++) {
			pheromones[i][bestSolution.tasks[i]] += 1.f;
		}
	}
	cout << "ACO End" << endl << "***" << endl;
	return bestSolution;
}

void ACOAlgorithm::initializePheromones() {
	pheromones.clear();
	pheromones.resize(instance.tasks.size(), vector<float>(instance.tasks.size(), INIT_PHEROMONE_VALUE));
}

Task& ACOAlgorithm::selectTask(SerialScheduleGenerator& ssg, Heuristic* heuristic) {
	float sum = 0;
	map<int, float> vals;
	const set<int>& tasks = ssg.getAvailableTasks();
	// calculate chances
	for (int taskId : tasks) {
		Task& task = instance.tasks[taskId];
		float val = pow(heuristic->getScore(task), heuristicExponent) *pow(pheromones[ssg.getNumberOfScheduledTasks()][taskId], pheromoneExponent);
		sum += val;
		vals.insert(pair<int, float>(taskId, val));
	}
	// roulette select
	float random = (rand() / (float)RAND_MAX * sum);
	float rouletteSum = 0.0000001f;
	for (int taskId : tasks) {
		rouletteSum += vals[taskId];
		if (rouletteSum >= random) {
			return instance.tasks[taskId];
		}
	}
	cout << "ERROR: No Task got selected!" << endl;
}