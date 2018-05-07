#pragma once
#include "Algorithm.h"
#include <vector>
#include <set>
#include <limits>
#include <map>

class SerialScheduleGenerator;
class Heuristic;

class ACOAlgorithm: public Algorithm {
	const float INIT_PHEROMONE_VALUE = 0.5f;

	float pheromoneExponent = 1.f;
	float heuristicExponent = 1.f;
	float evaporationRate = 0.85f;
	float minPhero = 0.5f;
	float maxPhero = 5.f;
	int ants = 100;

	std::vector<std::vector<float>> pheromones; // [position][task]

	void initializePheromones();
	Task& selectTask(SerialScheduleGenerator& ssg, Heuristic* heuristic);
public:
	ACOAlgorithm(Instance& instance) : Algorithm(instance) {};
	
	// Odziedziczono za poœrednictwem elementu Algorithm
	virtual Solution solve(int optimalMakespan) override;

	void setPheromoneExponent(float);
	void setHeuristicExponent(float);
	void setEvaporationRate(float);
	void setAntsPerIteration(int);
};