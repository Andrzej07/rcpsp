#include "stdafx.h"
#include "GPRWHeuristic.h"
#include <algorithm>

GPRWHeuristic::GPRWHeuristic(std::vector<Task>& tasks) {
	for (Task& task : tasks) {
		float score = task.time;
		for (int successor : task.successors) {
			score += tasks[successor].time;
		}
		scores.push_back(score);
	}
	float max = *max_element(scores.begin(), scores.end());
	for (int i = 0; i < scores.size(); i++) {
		scores[i] /= max;
	}

}

float GPRWHeuristic::getScore(Task task) {
	return scores[task.id];
}
