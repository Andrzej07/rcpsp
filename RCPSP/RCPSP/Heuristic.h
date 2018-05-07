#pragma once

class Task;

class Heuristic {
public:
	virtual float getScore(Task task) = 0;
};