// RCPSP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Reader.h"
#include "Solution.h"
#include "ACOAlgorithm.h"
#include "ABCAlgorithm.h"
#include "OptimalSolutions.h"
#include "Instance.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	Reader reader;

	int problemSize = 120;
	int param = 1;
	int instanceNumber = 4;

	OptimalSolutions os(problemSize);
	int optimalMakespan = os.getOptimalTimespan(param, instanceNumber);
	cout << "Optimal solution is: " << optimalMakespan << endl;
	Instance instance = reader.loadInstance(problemSize, param, instanceNumber);
	instance.print();

	Solution solution(instance);
	Algorithm* algorithm;
	//ACOAlgorithm aco(instance);
	//algorithm = &aco;
	ABCAlgorithm abc(instance);
	algorithm = &abc;

	solution = algorithm->solve(optimalMakespan);
	cout << endl << "Timespan: " << solution.calculateTimespan() << endl;

	int dummy;
	cin >> dummy;
    return 0;
}

