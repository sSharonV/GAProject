#pragma once

#include "GA_Evolution.h"
#include <time.h>
#include <vector>
#include <chrono>



using namespace std;
class GA_Population;

class GA_Chromosome {
	shared_ptr<vector<bool>> g_solution;
	shared_ptr<map<unsigned long, weak_ptr<Ded_Block>>> g_blocks;
	long double g_solSize;
	long double g_solLimit;
	
public:
	int g_id;
	GA_Chromosome(unsigned long num_blocks = 1, long double limit = 0, int id = -1);
	GA_Chromosome(const GA_Chromosome &other);
	~GA_Chromosome();
	long double ObjectiveFunc() const;
	void InitSolution();
	void AttachMyBlocks();
	bool CheckIndex(unsigned long index);
	void SetIndex(unsigned long index, bool val);
private:
	void setSizeInBytes(long double s);
};

