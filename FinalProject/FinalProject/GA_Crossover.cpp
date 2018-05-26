#include "GA_Crossover.h"

GA_Crossover::GA_Crossover(Crossover cros) : s_cros_mode(cros)
{
	
}

GA_Crossover::~GA_Crossover()
{
}

void GA_Crossover::GenerateOffprings(shared_ptr<GA_Population> cur_pool)
{
	unsigned long num_blocks;
	long double limit;
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());

	s_newGeneration = make_shared<vector<shared_ptr<GA_Chromosome>>>(
		vector<shared_ptr<GA_Chromosome>>()
		);

	while (s_newGeneration->size() != mig_ptr->GetProperties()->g_elit_best)
		s_newGeneration->push_back(cur_pool->GetChromosomes()->at(s_newGeneration->size()));

	chromo_1 = make_shared<GA_Chromosome>(GA_Chromosome());
	chromo_2 = make_shared<GA_Chromosome>(GA_Chromosome());
	offspring_1 = make_shared<GA_Chromosome>(GA_Chromosome());
	offspring_2 = make_shared<GA_Chromosome>(GA_Chromosome());
		
	num_blocks = mig_ptr->GetBlocks()->size();
	limit = mig_ptr->GetProperties()->g_KBforMig;
	CrossImplement(cur_pool, num_blocks, limit);

}

shared_ptr<vector<shared_ptr<GA_Chromosome>>> GA_Crossover::GetNewGeneration()
{
	return s_newGeneration;
}
