#pragma once
#ifndef MIGRATION_H
#include "GA_Migration.h"
#endif
#ifndef POPULATION_H
#include "GA_Population.h"
#endif
#ifndef SELECTION_H
#include "GA_Selection.h"
#endif
#ifndef SELECTIONRW_H
#include "GA_SelectionRW.h"
#endif

using namespace std;

class GA_Population;
class GA_Migration;
class GA_Selection;
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

