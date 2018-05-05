#pragma once
#include "GA_Chromosome.h" 
#include "GA_Migration.h"
#include <vector>

using namespace std;

class GA_Chromosome;

class GA_Population {
	vector<GA_Chromosome> p_chromosomes;
	int size;
public:
	GA_Population(int size = 10);
	bool Initialize();
};