#include "GA_Selection.h"

GA_SelectionLRB::GA_SelectionLRB(Selection sel, int elit, long double max) : GA_Selection(sel, elit) , m_MAX(max){
	m_MIN = 2 - m_MAX;
}

void GA_SelectionLRB::SelectImplement(shared_ptr<GA_Population> sh_p)
{
	long int sum_rank;
	long double ch_percent;
	vector< shared_ptr<GA_Chromosome>> t_chrom;
	// Initialize a copy of current population
	t_chrom = *(sh_p->GetChromosomes());

	//	Initializing the pointer for new population to return
	m_N = sh_p->GetPopSize();
	s_matingPool = make_shared<GA_Population>(GA_Population(m_N));

	// Initializing sum of ranks
	sum_rank = 0;
	for (int i = 1; i < m_N + 1; i++)
		sum_rank += i;

	//	Saves fixed number of best-fitted chromosomes from the current population
	if (s_elit != 0) InitElitism();

	// Random protocol
	int p_rand;
	srand(time(NULL));

	//	Sort the vector with the following lambda-function (supported by C++)
	sort(t_chrom.begin(), t_chrom.end(),
		//	- Sort being processed with the objective function value of the chromosomes
		[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
		return o1->ObjectiveFunc() < o2->ObjectiveFunc();
	});

	// Start attaching chromosomes to the mating pool
	while (s_matingPool->GetChromosomes()->size() != m_N) {	// Untill the mating pool is full with selected chromosomes
		int i = m_N;
		for (auto it_chr = t_chrom.begin(); it_chr != t_chrom.end(); it_chr++) {
			p_rand = rand() % sum_rank + 1;						// Range [1,sum_rank]
			ch_percent = (long double)((CalcExpVal(i) / m_N) * (100.0));
			i--;
			if (p_rand < ch_percent)
				s_matingPool->InitBySelect(*it_chr);
			if (s_matingPool->GetChromosomes()->size() == m_N)
				break;
		}
	}
}


long double GA_SelectionLRB::CalcExpVal(long double p_rank) {

	return (m_MIN + ((m_MAX - m_MIN)*((p_rank)-1) / (m_N - 1)));
}