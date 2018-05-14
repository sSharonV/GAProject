#include "GA_Selection.h"

GA_SelectionTS::GA_SelectionTS(Selection sel, int elit, int num_comp) : GA_Selection(sel, elit), m_k_competitors(num_comp)
{
}

void GA_SelectionTS::SelectImplement(shared_ptr<GA_Population> sh_p)
{
	vector< shared_ptr<GA_Chromosome>> t_chrom;
	vector<	shared_ptr<GA_Chromosome>> t_chrom_tour;

	// Initialize a copy of current population
	t_chrom = *(sh_p->GetChromosomes());

	// Initialize vector for the tournament
	t_chrom_tour = vector<shared_ptr<GA_Chromosome>>();

	//	Initializing the pointer for new population to return
	s_matingPool = make_shared<GA_Population>(GA_Population(sh_p->GetPopSize()));

	//	Saves fixed number of best-fitted chromosomes from the current population
	if (s_elit != 0) InitElitism();

	// Random protocol
	int p_rand;
	srand(time(NULL));

	while (s_matingPool->GetChromosomes()->size() != sh_p->GetPopSize()) {
		//	Generate 'm_k_competitors' competitors 
		while (t_chrom_tour.size() != m_k_competitors) {
			p_rand = rand() % sh_p->GetPopSize();
			t_chrom_tour.push_back(t_chrom.at(p_rand));
		}
		PerformTournament(t_chrom_tour);
	}
}

void GA_SelectionTS::PerformTournament(vector<shared_ptr<GA_Chromosome>> competitors)
{
	//	Sort the vector with the following lambda-function (supported by C++)
	sort(competitors.begin(), competitors.end(),
		//	- Sort being processed with the objective function value of the chromosomes
		[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
		return o1->ObjectiveFunc() < o2->ObjectiveFunc();
	});
	s_matingPool->InitBySelect(competitors.at(0));
}
