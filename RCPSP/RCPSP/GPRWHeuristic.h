#pragma once
#include "Heuristic.h"
#include <vector>

class GPRWHeuristic : public Heuristic {
private:
	std::vector<float> scores;

public:
	GPRWHeuristic(std::vector<Task>& tasks);

	// Odziedziczono za poœrednictwem elementu Heuristic
	virtual float getScore(Task task) override;
};