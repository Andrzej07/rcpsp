#include "stdafx.h"
#include "ABCAlgorithm.h"
#include "Solution.h"
#include "SerialScheduleGenerator.h"
#include <limits>

using namespace std;

struct PriorityList {
private:
	vector<float> priorities;
	int calculatedMakespan = -1;
	Solution* solution = nullptr;

public:
	PriorityList(int size) {
		priorities.reserve(size);
		for (int i = 0; i < size; i++) {
			priorities.push_back(rand() / (float)RAND_MAX);
		}
	}

	PriorityList(const PriorityList& pl) {
		priorities = pl.priorities;
		calculatedMakespan = pl.calculatedMakespan;
		solution = new Solution(*pl.solution);
	}

	~PriorityList() {
		delete(solution);
	}

	PriorityList(PriorityList& base, PriorityList& neighbour) {
		priorities.reserve(base.priorities.size());
		for (int i = 0; i < base.priorities.size(); i++) {
			float val = base.priorities[i] + (rand() / (RAND_MAX / 2.f) - 1.f) * (base.priorities[i] - neighbour.priorities[i]);
			if (val > 1.f) val = 1.f;
			else if (val < 0) val = 0;
			priorities.push_back(val);
		}
	}

	int modify(PriorityList& neighbour) {
		calculatedMakespan = -1;
		int pos = rand() % priorities.size();
		priorities[pos] += (rand() / (RAND_MAX / 2.f) - 1.f) * (priorities[pos] - neighbour.priorities[pos]);
		return pos;
	}

	int calculateMakespan(Instance& instance) {
		if (calculatedMakespan != -1) {
			return calculatedMakespan;
		}
		SerialScheduleGenerator sgs(instance);
		while (!sgs.isFinished()) {
			int taskToAdd = 0;
			float highestPriority = -1.f;
			for (int taskId : sgs.getAvailableTasks()) {
				if (priorities[taskId] > highestPriority) {
					taskToAdd = taskId;
					highestPriority = priorities[taskId];
				}
			}
			sgs.addTask(instance.tasks[taskToAdd]);
		}
		solution = new Solution(sgs.getSolution());
		calculatedMakespan = solution->calculateTimespan();
		return calculatedMakespan;
	}

	Solution* getSolution() {
		return solution;
	}

	void acceptChanges(int pos, PriorityList& pl) {
		priorities[pos] = pl.priorities[pos];
		calculatedMakespan = pl.calculatedMakespan;
		solution = new Solution(*pl.solution);
	}
	
};

int getRandomDifferentThan(int max, int x) {
	int val;
	do {
		val = rand() % max;
	} while (val == x);
	return val;
}

Solution ABCAlgorithm::solve(int optimalMakespan) {
	cout << "***" << endl << "ABC Start" << endl;
	Solution bestSolution(instance);
	vector<PriorityList> foodSources;
	bool solInitialized = false;
	foodSources.reserve(population / 2);
	for (int i = 0; i < population / 2; i++) {
		PriorityList pl(instance.tasks.size());
		int makespan = pl.calculateMakespan(instance);
		if (!solInitialized || makespan < bestSolution.getCalculatedTimespan()) {
			solInitialized = true;
			bestSolution = Solution(*pl.getSolution());
		}
		foodSources.push_back(pl);
	}
	cout << "Best solution from initial population: " << bestSolution.getCalculatedTimespan() << endl;
	if (bestSolution.getCalculatedTimespan() == optimalMakespan) {
		return bestSolution;
	}
	vector<int> trials(foodSources.size(), 0);

	for (int iteration = 0; iteration < 50; iteration++) {
		cout << "Iteration: " << iteration+1 << endl;
		// employed bees
		for (int i = 0; i < foodSources.size(); i++) {
			PriorityList candidate(foodSources[i]);
			int modifiedPos = candidate.modify(foodSources[getRandomDifferentThan(foodSources.size(), i)]);
			int makespan = candidate.calculateMakespan(instance);
			if (makespan < foodSources[i].calculateMakespan(instance)) {
				if (makespan == optimalMakespan) {
					return Solution(*candidate.getSolution());
				} else if (bestSolution.getCalculatedTimespan() > makespan) {
					foodSources[i].acceptChanges(modifiedPos, candidate);
					cout << "Improving solution to: " << candidate.calculateMakespan(instance) << endl;
					bestSolution = Solution(*foodSources[i].getSolution());
				}
			} else {
				trials[i]++;
			}
		}
		// onlooker bees
		vector<float> chances;
		float rouletteSum = 0;
		for (PriorityList& pl : foodSources) {
			float val = 1 / (float)pl.calculateMakespan(instance);
			rouletteSum += val;
			chances.push_back(val);
		}
		float rouletteRandCoeff = rouletteSum / (float)RAND_MAX;
		for (int i = 0; i < foodSources.size(); i++) {
			PriorityList candidate(foodSources[i]);
			float sum = 0.000000001f;
			float rouletteRand = rand() * rouletteRandCoeff;
			int selectedFood = 0;
			for (int j = 0; j < chances.size(); j++) {
				sum += chances[j];
				if (sum >= rouletteRand) {
					selectedFood = j;
					break;
				}
			}
			int modifiedPos = candidate.modify(foodSources[selectedFood]);
			if (candidate.calculateMakespan(instance) < foodSources[i].calculateMakespan(instance)) {
				if (candidate.calculateMakespan(instance) == optimalMakespan) {
					return Solution(*candidate.getSolution());
				} else if (bestSolution.getCalculatedTimespan() > candidate.calculateMakespan(instance)) {
					foodSources[i].acceptChanges(modifiedPos, candidate);
					cout << "Improving solution to: " << candidate.calculateMakespan(instance) << endl;
					bestSolution = Solution(*foodSources[i].getSolution());
				}
			} else {
				trials[i]++;
			}

		}
		// scout bees
		int maxTrial = 0;
		int chosenFoodSource = 0;
		for (int i = 0; i < trials.size(); i++) {
			if (trials[i] > maxTrial) {
				maxTrial = trials[i];
				chosenFoodSource = i;
			}
		}
		foodSources[chosenFoodSource] = PriorityList(instance.tasks.size());
		foodSources[chosenFoodSource].calculateMakespan(instance);
	}

	
	return bestSolution;
}
