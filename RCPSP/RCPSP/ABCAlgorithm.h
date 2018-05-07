#pragma once
#include "Algorithm.h"

class ABCAlgorithm : public Algorithm {
	int population = 100;
	int maxTrial = 5;
	//int scouts = 20;

public:
	ABCAlgorithm(Instance& instance) : Algorithm(instance) {};

	// Odziedziczono za poœrednictwem elementu Algorithm
	virtual Solution solve(int) override;
};