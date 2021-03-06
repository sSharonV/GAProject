#include "GA_Selection.h"

GA_SelectionTS::GA_SelectionTS(Selection sel, int elit, int num_comp) : GA_Selection(sel, elit), m_k_competitors(num_comp)
{
}

void GA_SelectionTS::SelectImplement(shared_ptr<GA_Population> sh_p)
{
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());

	vector< shared_ptr<GA_Chromosome>> t_chrom;
	vector<	shared_ptr<GA_Chromosome>> t_chrom_tour;

	// Initialize a copy of current population
	t_chrom = *(sh_p->GetChromosomes());

	// Initialize vector for the tournament
	t_chrom_tour = vector<shared_ptr<GA_Chromosome>>();

	//	Saves fixed number of best-fitted chromosomes from the current population
	if (s_elit != 0) InitElitism();

	// Random protocol
	int p_rand;
	srand(time(NULL));

	while (ga_evo->GetMatingPool()->GetChromosomes()->size() != sh_p->GetPopSize()) {
		//	Generate 'm_k_competitors' competitors 
		while (t_chrom_tour.size() != m_k_competitors) {
			p_rand = rand() % sh_p->GetPopSize();
			if(!t_chrom.at(p_rand)->GetTimedOut())
				t_chrom_tour.push_back(t_chrom.at(p_rand));
		}
		PerformTournament(t_chrom_tour);
	}
}

void GA_SelectionTS::PerformTournament(vector<shared_ptr<GA_Chromosome>> competitors)
{
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
	//	Sort the vector with the following lambda-function (supported by C++)
	sort(competitors.begin(), competitors.end(),
		//	- Sort being processed with the objective function value of the chromosomes
		[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
		return o1->ObjectiveFunc() < o2->ObjectiveFunc();
	});
	ga_evo->GetMatingPool()->InitBySelect(competitors.at(0));
}
