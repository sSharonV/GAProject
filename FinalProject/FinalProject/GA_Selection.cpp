#include "GA_Selection.h"

GA_Selection::GA_Selection(Selection sel, int elit) : s_sel_mode(sel), s_elit(elit) {
	
}

GA_Selection::~GA_Selection()
{
	if (s_popul.expired())
		s_popul.reset();
}

void GA_Selection::InitElitism()
{
	int cnt = 0;
	vector<shared_ptr<GA_Chromosome>> t_chrom;
	if (auto sh_pop = s_popul.lock()) {
		t_chrom = *(sh_pop->GetChromosomes());
		sort(t_chrom.begin(), t_chrom.end(), 
				[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) 
				{
					return o1->ObjectiveFunc() < o2->ObjectiveFunc();
				}
			);
		for (cnt; cnt < s_elit; cnt++)
			s_matingPool->InitBySelect(t_chrom.at(cnt));
	}
}



