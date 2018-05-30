#pragma once

#include "GA_Evolution.h"
#include <time.h>
#include <vector>
#include <chrono>

using namespace std;
class GA_Population;

/*
	Chromosome is a representation of solution.
	-	Every solution consists of weak_ptr to its original blocks
*/
class GA_Chromosome {
	/*
		Boolean vector for storing the descisions for migrating blocks
	*/
	shared_ptr<vector<bool>> g_solution;

	/*
		Map of the associated blocks of this solution
	*/
	shared_ptr<map<unsigned long, weak_ptr<Ded_Block>>> g_blocks;

	/*
		Total Solution size in bytes
	*/
	long double g_solSize;

	/*
		Size which found for migration - without considering the size of neighboors
	*/

	long double g_migratedSize;
	/*
		Size for solution in bytes
	*/
	long double g_solLimit;
	
public:
	int g_id;
	GA_Chromosome(unsigned long num_blocks = 1, long double limit = 0, int id = -1);
	GA_Chromosome(const GA_Chromosome &other);
	~GA_Chromosome();
	shared_ptr<map<unsigned long, weak_ptr<Ded_Block>>> GetMyBlocks();
	bool CheckIndex(unsigned long index);
	void SetIndex(unsigned long index, bool val);
	long double GetSolSize();
	long double GetMigSize();
	void setSizeInBytes(long double s);

	/*
		Objective function is the additional size between the requeseted size (by the user) compared to physical size of the current solution
		-	if the objective function is negative, we will relate to it as 0
	*/
	long double ObjectiveFunc() const;

	/*
		Initialization of a solution will attach blocks to chromosome - up to requirments
		-	The solution is feasible solution to the problem
		-	Chromosome has map of it's pointed blocks
	*/
	void InitSolution();
	
	/*
		A given chromosome might be initialized with a boolean vector that doesn't represent feasible solution
		-	To fix this, the method will search ,for every migrating block, his neighboors - and attach them to the solution size as well
	*/
	void FixToFeasibleSol();

	/*
		Takes care of updating g_blocks for an modified chromosome
		-	Being used by GA_Crossover, after generating new offspring
	*/
	void AttachMyBlocks();
};

