#include "GA_Selection.h"

GA_SelectionRW::GA_SelectionRW(Selection sel, int elit) : GA_Selection(sel,elit)
{
}

void GA_SelectionRW::SelectImplement(shared_ptr<GA_Population> sh_p)
{
	int size;
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());

	auto sh_chr = sh_p->GetChromosomes();

	//	Calculate current total fitness(updates @size)
	m_totalFit = 0;
	for (auto it_chr : *sh_chr) 	// for each population's chromosome
		m_totalFit += it_chr->ObjectiveFunc();

	//	Initializing the pointer for new population to return
	size = sh_p->GetPopSize();

	//	Saves fixed number of best-fitted chromosomes from the current population
	if (s_elit != 0) InitElitism();

	// Random protocol
	int p_rand;
	srand(time(NULL));

	// Start attaching chromosomes to the mating pool
	while (ga_evo->GetMatingPool()->GetChromosomes()->size() != size) {	// Untill the mating pool is full with selected chromosomes
		for (auto it_chr : *(sh_p->GetChromosomes())) {
			p_rand = rand() % 100 + 1;							// Range [1,100]
			if (p_rand < CalcPercent(it_chr->ObjectiveFunc()))
				ga_evo->GetMatingPool()->InitBySelect(it_chr);
			if (ga_evo->GetMatingPool()->GetChromosomes()->size() == size)
				break;
		}
	}
}

/*
	Calculates the probability for chromosome to be chosen
	-	ob.f = 0 -> probability = 100%
	-	the more the ob.f value is greater, the percentage will be lower...
*/
double GA_SelectionRW::CalcPercent(long double cardinal)
{
	if (m_totalFit == 0) return 100.0;
	return (100.0 - ((cardinal / m_totalFit)*100.0));
}