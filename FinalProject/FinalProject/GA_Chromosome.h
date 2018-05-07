#pragma once
#include "GA_Evolution.h"
#include <time.h>
#include <vector>
#include <chrono>

using namespace std;
class GA_Population;

class GA_Chromosome {
	vector<bool> g_solution;
	map<unsigned long, Ded_Block*> g_blocks;
	unsigned long g_solSize;
	unsigned long g_solLimit;
public:
	GA_Chromosome(unsigned long limit = 0);
	unsigned long getSizeInBytes();
	
	void InitSolution();
private:
	void setSizeInBytes(unsigned long s);
};
