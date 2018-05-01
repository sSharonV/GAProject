#pragma once
#include <vector>

using namespace std;

class GA_Chromosome {
	vector<bool> g_solution;
	unsigned long g_solSize;
public:
	GA_Chromosome(int size);
	unsigned long getSizeInBytes();
	void setSizeInBytes();
	
};
