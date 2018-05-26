#pragma once
#include "GA_Evolution.h"

using namespace std;

class GA_Evolution;
class GA_Migration;
class GA_Population;
class GA_Chromosome;

enum class Crossover;

/*
	Abstract class which handles the main functions of crossover operation
	-	Non-defiened (Abstract) function for crossovering chromosomes
	-	Definition of the function which Initializing the objects which are needed for the operations
*/
class GA_Crossover {
protected:
	/*
		2 Chromosomes which are modified by crossover operation
	*/
	shared_ptr<GA_Chromosome> chromo_1, chromo_2;

	/*
		2 Chromosomes which are the children whom are created by crossover operation
	*/
	shared_ptr<GA_Chromosome> offspring_1, offspring_2;
	
	/*
		Crossover model
	*/
	Crossover s_cros_mode;

	/*
		Pointer to vector which consists of new offsprings
	*/
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> s_newGeneration;
public:
	GA_Crossover(Crossover cros);
	~GA_Crossover();
	shared_ptr<vector<shared_ptr<GA_Chromosome>>> GetNewGeneration();

	/*
		Initializing the objects and executing the implementation for the crossover operation
	*/
	void GenerateOffprings(shared_ptr<GA_Population> cur_pool);
	
private:
	/*
		Using specific implementation according to the derived class
	*/
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit) = 0;
};

/*
	Derived class of GA_Crossover which implements the One-Point crossover
	-	A border is defined in the middle of each chromosome
	-	The information of the chromosomes getting swapped between the parents
*/
class GA_CrossoverOP : public GA_Crossover {
public:
	GA_CrossoverOP(Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};

/*
Derived class of GA_Crossover which implements the Two-Point crossover
-	2 borders are defined in each chromosome
-	The information of the chromosomes getting swapped between the parents
*/
class GA_CrossoverTP : public GA_Crossover {
public:
	GA_CrossoverTP(Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};

/*
Derived class of GA_Crossover which implements the Uniform crossover
-	Mask of binary values is generated randomly
-	The information of the chromosomes getting swapped between the parents
*/
class GA_CrossoverU : public GA_Crossover {
public:
	GA_CrossoverU(Crossover cros);
	virtual void CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit);
};