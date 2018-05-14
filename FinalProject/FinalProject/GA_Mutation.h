#pragma once

#include "GA_Evolution.h"

class GA_Evolution;
class GA_Migration;
class GA_Population;
class GA_Chromosome;

enum class Mutation;

class GA_Mutation {
	Mutation s_mut_mode;
	int s_mut_chance;
	weak_ptr<vector<shared_ptr<GA_Chromosome>>> s_newGen;
public:
	GA_Mutation(Mutation mut, shared_ptr<vector<shared_ptr<GA_Chromosome>>> curr_pop, int chance);
	~GA_Mutation();
	void PerformMutation();
private:
	void PerformSingle(shared_ptr<GA_Chromosome> toMut);
	void PerformUniform(shared_ptr<GA_Chromosome> toMut);
};