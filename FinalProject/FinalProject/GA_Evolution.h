#pragma once
#include "GA_Migration.h"
#include "GA_Population.h"
#include "GA_Selection.h"
#include "GA_Crossover.h"
#include "GA_Mutation.h"

using namespace std;

class GA_Population;
class GA_Migration;
class GA_Selection;
class GA_Crossover;
class GA_Mutation;

/*
	Evolution has the methods to start the evolution process of the Genetic-Algorithm, and retrive populations which were constructed during it
*/
class GA_Evolution {

	/*
		Pointer to current population of a given generation
	*/
	shared_ptr<GA_Population> m_popu;

	/*
		Mating pool which will be used by the evolution process
	*/
	shared_ptr<GA_Population> m_matingPool;

	/*
		Initial population of the execution
	*/
	shared_ptr<GA_Population> m_Initialpopu;

	/*
		Maps for converting indexes of blocks to block_sn and vica versa
	*/
	map<unsigned long, string> indexes_to_keys;
	map<string, unsigned long> keys_to_indexes;

public:
	static shared_ptr<GA_Evolution> GetCurInstance();
	map<unsigned long, string> GetInToKe();
	map<string, unsigned long> GetKeToIn();
	shared_ptr<GA_Population> GetCurPopulation();
	shared_ptr<GA_Population> GetMatingPool();
	shared_ptr<GA_Population> GetInitialPopulation();
	void SetMatingPool(GA_Population new_pop);
	void InitEvolution();
	/*
		Takes care of generating initial population and starting the loop of the evolution process
		-	Initial Population - consists of chromosomes which generates by a random attachment of blocks to a chromosome,
			up to a given size by the user
		-	Loop consists of performing Selection, Crossover and mutation operations
	*/
	void StartEvolution();
private:
	GA_Evolution();
};

