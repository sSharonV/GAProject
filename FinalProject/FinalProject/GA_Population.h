#pragma once
#include "GA_Evolution.h" 
#ifndef CHROMOSOME_H
#include "GA_Chromosome.h"
#endif // !CHROMOSOME_H

using namespace std;

class GA_Chromosome;
class GA_Evolution;

class GA_Population {
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> p_chromosomes;
	int p_size;
public:
	GA_Population(int size);
	GA_Population();
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> GetChromosomes();
	void Initialize();
	void InitBySelect(shared_ptr<GA_Chromosome> push_chr);
	int GetPopSize();

};