#pragma once
#include "GA_Migration.h"
#include "GA_Population.h"
//#include "GA_Chromosome.h"
using namespace std;

class GA_Population;

class GA_Evolution {
	//GA_Population *m_popu;
	map<unsigned long, string> indexes_to_keys;
	map<string, unsigned long> keys_to_indexes;
public:
	static GA_Evolution* GetCurInstance();
	GA_Evolution();
	map<unsigned long, string> GetInToKe();
	map<string, unsigned long> GetKeToIn();
	void InitEvolution();
	void StartEvolution();
};
