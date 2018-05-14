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
//class GA_SelectionRW;

class GA_Evolution {
	shared_ptr<GA_Population> m_popu;
	map<unsigned long, string> indexes_to_keys;
	map<string, unsigned long> keys_to_indexes;
public:
	static shared_ptr<GA_Evolution> GetCurInstance();
	map<unsigned long, string> GetInToKe();
	map<string, unsigned long> GetKeToIn();
	shared_ptr<GA_Population> GetCurPopulation();
	void InitEvolution();
	void StartEvolution();
private:
	GA_Evolution();
};

