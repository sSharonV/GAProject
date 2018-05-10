#pragma once
#include "GA_Evolution.h"
#include <time.h>
#include <vector>
#include <chrono>

using namespace std;
class GA_Population;

class GA_Chromosome {
	shared_ptr<vector<bool>> g_solution;
	shared_ptr<map<unsigned long, weak_ptr<Ded_Block>>> g_blocks;
	long double g_solSize;
	long double g_solLimit;
public:
	GA_Chromosome(unsigned long num_blocks = 1, long double limit = 0);
	~GA_Chromosome();
	long double getSizeInBytes();
	void InitSolution();
private:
	void setSizeInBytes(long double s);
};

