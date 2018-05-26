#pragma once

#include "GA_Evolution.h"

class GA_Evolution;
class GA_Migration;
class GA_Population;
class GA_Chromosome;

enum class Mutation;

/*
	Handles main functions of mutation operation
	-	Perform single\uniform mutation on a given chromosome
*/
class GA_Mutation {
	/*
		Mutation model
	*/
	Mutation s_mut_mode;

	/*
		Chance for mutation
	*/
	int s_mut_chance;
	
public:
	GA_Mutation(Mutation mut, int chance);
	~GA_Mutation();

	/*
		Peforming mutation on the chromosomes which are not included by Elitism
	*/
	void PerformMutation(shared_ptr<vector<shared_ptr<GA_Chromosome>>> newGen);
private:
	/*
		Randomly chooses a bit to flip within a solution
	*/
	void PerformSingle(shared_ptr<GA_Chromosome> toMut);

	/*
		For each bit perform random flip of it
	*/
	void PerformUniform(shared_ptr<GA_Chromosome> toMut);
};