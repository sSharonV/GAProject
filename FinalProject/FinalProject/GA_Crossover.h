#pragma once
#include "GA_Evolution.h"

using namespace std;

class GA_Evolution;
class GA_Migration;
class GA_Population;
class GA_Chromosome;

enum class Crossover;

class GA_Crossover {
protected:
	shared_ptr<GA_Chromosome> chromo_1, chromo_2;
	shared_ptr<GA_Chromosome> offspring_1, offspring_2;
	Crossover s_cros_mode;
	weak_ptr<GA_Population> s_currMatingPool;
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> s_newGeneration;
public:
	GA_Crossover(shared_ptr<GA_Population> cur_pool, Crossover cros);
	~GA_Crossover();
	void InitPtr(shared_ptr<GA_Chromosome> chromo);
	void GenerateOffprings();
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> GetNewGeneration();
private:
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit) = 0;

};

class GA_CrossoverOP : public GA_Crossover {
public:
	GA_CrossoverOP(shared_ptr<GA_Population> cur_pool, Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};

class GA_CrossoverTP : public GA_Crossover {
public:
	GA_CrossoverTP(shared_ptr<GA_Population> cur_pool, Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};

class GA_CrossoverU : public GA_Crossover {
public:
	GA_CrossoverU(shared_ptr<GA_Population> cur_pool, Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};