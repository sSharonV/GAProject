#pragma once
#include "GA_Chromosome.h" 
#include <vector>

using namespace std;

class GA_Chromosome;

class GA_Population {
	vector<GA_Chromosome> p_chromosomes;
public:
	GA_Population();
};