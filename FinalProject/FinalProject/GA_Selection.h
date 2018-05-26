#pragma once
#include "GA_Evolution.h"
#include <algorithm>

using namespace std;

class GA_Evolution;
class GA_Migration;
class GA_Population;
class GA_Chromosome;

enum class Selection;

/*
	Abstract class which handles the main functions of selection operation
	-	Non-defiened (Abstract) function for initializing the mating-pool
	-	Definition of the function which saves the best fitted chromosomes
		of the current population (Elitism concept)
	-	A destructor for the class which releasing the weak_ptr of derived classes
*/
class GA_Selection {
protected:
	/*
		Selection model
	*/
	Selection s_sel_mode;

	/*
		Number of saved chromosomes (Elitism)
	*/
	int s_elit;
public:
	GA_Selection(Selection sel, int elit);
	~GA_Selection();
	
	/*
		Initializing the mating pool from GA_Evolution and executing the specific selection implemention
	*/
	void InitMatingPool(shared_ptr<GA_Population> population);
	// virtual saved-word is for commanding the compiler to use the definition of the derived class
	virtual void SelectImplement(shared_ptr<GA_Population> sh_p) = 0;
protected:

	/*
		Takes care of initializing the mating pool with the best fitted chromosomes of the current population
		-	Up to 's_elit' num of chromosomes
	*/
	void InitElitism();
};

/*
	Derived class of GA_Selection which implements the Roulette-Wheel selection
	-	Each chromosome has a chance to be included to the mating pool,
		which is proportional to his Fitness-value
	-	Fitness value is calculated with GA_Chromosome::ObjectiveFunc()
*/
class GA_SelectionRW : public GA_Selection {
	long double m_totalFit;
public:
	GA_SelectionRW(Selection sel, int elit);
	virtual void SelectImplement(shared_ptr<GA_Population> sh_p);
private:
	/*
		Calculate the propability for a chromosome to be selected 
		-	The more lower fitness value, the higher chance to be selected
	*/
	double CalcPercent(long double cardinal);
};

/*
	Derived class of GA_Selection which implements the Linear-Rank based selection
	-	Each chromosome getting a rank value which is a value between 1 to N, when N
		is the number of chromosomes in a given population
	-	Expected value formula can be seen in the project book
*/
class GA_SelectionLRB : public GA_Selection {
	long double m_MAX;
	long double m_MIN;
	int m_N;
public:
	GA_SelectionLRB(Selection sel, int elit, long double max = 2.0);
	virtual void SelectImplement(shared_ptr<GA_Population> sh_p);
private:
	/*
		Calculate the expected value of a given chromosome according to linear-rank
	*/
	long double CalcExpVal(long double p_rank);
};

/*
	Derived class of GA_Selection which implements the Tournament selection
	-	Each tournament consist of k random picked chromosomes from the current population
	-	Mating pool consists of the winners of each tournament that is performed
*/
class GA_SelectionTS : public GA_Selection {
	int m_k_competitors;
public:
	GA_SelectionTS(Selection sel, int elit, int num_comp = 5);
	virtual void SelectImplement(shared_ptr<GA_Population> sh_p);
private:
	/*
		Returns the winner of a given chromosomes
	*/
	void PerformTournament(vector<shared_ptr<GA_Chromosome>> competitors);
};