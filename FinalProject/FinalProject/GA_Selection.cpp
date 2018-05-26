#include "GA_Selection.h"

GA_Selection::GA_Selection(Selection sel, int elit) : s_sel_mode(sel), s_elit(elit) {
	
}

GA_Selection::~GA_Selection()
{
}

void GA_Selection::InitMatingPool(shared_ptr<GA_Population> population)
{
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());

	//	Reallocating the mating-pool 
	ga_evo->SetMatingPool(GA_Population(ga_evo->GetCurPopulation()->GetPopSize()));

	//	Specific implement to execute...
	SelectImplement(population);
}


void GA_Selection::InitElitism()
{
	vector<shared_ptr<GA_Chromosome>> t_chrom;
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
	
	t_chrom = *ga_evo->GetCurPopulation()->GetChromosomes();

	//	Sort the vector with the following lambda-function (supported by C++)
	sort(t_chrom.begin(), t_chrom.end(), 
			//	- Sort being processed with the objective function value of the chromosomes
			[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
				return o1->ObjectiveFunc() < o2->ObjectiveFunc();
			});
			
	// Take 's_elit' chromosomes from the ordered vector
	for (int cnt = 0; cnt < s_elit; cnt++)
		ga_evo->GetMatingPool()->InitBySelect(t_chrom.at(cnt));
}



