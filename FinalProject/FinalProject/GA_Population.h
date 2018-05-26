#pragma once
#include "GA_Evolution.h" 
#include "GA_Chromosome.h"

using namespace std;

class GA_Chromosome;
class GA_Evolution;

/*
	Consists of chromosome vector and the size of a population
*/
class GA_Population {
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> p_chromosomes;
	int p_size;
public:
	GA_Population(int size);
	GA_Population(vector<shared_ptr<GA_Chromosome>> chromosomes);
	GA_Population();
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> GetChromosomes();
	int GetPopSize();

	/*
		Start the initialization of p_size chromosome as feasible solutions
	*/
	void Initialize();

	/*
		Adds chromosome to population
	*/
	void InitBySelect(shared_ptr<GA_Chromosome> push_chr);
};