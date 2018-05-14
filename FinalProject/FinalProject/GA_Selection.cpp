#include "GA_Selection.h"

GA_Selection::GA_Selection(Selection sel, int elit) : s_sel_mode(sel), s_elit(elit) {
	
}

GA_Selection::~GA_Selection()
{
	if (s_popul.expired())
		s_popul.reset();
}

void GA_Selection::InitMatingPool(shared_ptr<GA_Population> population)
{
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
	s_matingPool = make_shared<GA_Population>(GA_Population());

	//	Managing weak reference to CURRENT population within GA_Evolution class
	s_popul = ga_evo->GetCurPopulation();
	if (auto sh_pop = s_popul.lock()) {
		SelectImplement(sh_pop);
	}
}

shared_ptr<GA_Population> GA_Selection::GetCurrentPool()
{
	return s_matingPool;
}

/*
	Takes care of initializing the mating pool with the best fitted chromosomes of the current population
	-	Up to 's_elit' num of chromosomes
*/
void GA_Selection::InitElitism()
{
	vector<shared_ptr<GA_Chromosome>> t_chrom;
	if (auto sh_pop = s_popul.lock()) {
		t_chrom = *(sh_pop->GetChromosomes());

		//	Sort the vector with the following lambda-function (supported by C++)
		sort(t_chrom.begin(), t_chrom.end(), 
				//	- Sort being processed with the objective function value of the chromosomes
				[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
					return o1->ObjectiveFunc() < o2->ObjectiveFunc();
				});
			
		// Take 's_elit' chromosomes from the ordered vector
		for (int cnt = 0; cnt < s_elit; cnt++)
			s_matingPool->InitBySelect(t_chrom.at(cnt));
	}
}



