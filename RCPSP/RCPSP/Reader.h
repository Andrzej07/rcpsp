#pragma once
#include <string>

class Instance;

class Reader {
public:
	Instance loadInstance(int problemSize, int param, int instance);
	Instance loadInstance(std::string path);
};