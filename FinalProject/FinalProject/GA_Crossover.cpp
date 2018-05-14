#include "GA_Crossover.h"

GA_Crossover::GA_Crossover(shared_ptr<GA_Population> cur_pool, Crossover cros) : s_cros_mode(cros)
{
	s_currMatingPool = cur_pool;
	s_newGeneration = make_shared<vector<shared_ptr<GA_Chromosome>>>(
		vector<shared_ptr<GA_Chromosome>>()
		);
	chromo_1 = make_shared<GA_Chromosome>(GA_Chromosome());
	chromo_2 = make_shared<GA_Chromosome>(GA_Chromosome());
	offspring_1 = make_shared<GA_Chromosome>(GA_Chromosome());
	offspring_2 = make_shared<GA_Chromosome>(GA_Chromosome());
}

GA_Crossover::~GA_Crossover()
{
	if (s_currMatingPool.expired())
		s_currMatingPool.reset();
}

void GA_Crossover::InitPtr(shared_ptr<GA_Chromosome> chromo)
{
	chromo = make_shared<GA_Chromosome>(GA_Chromosome());
}

void GA_Crossover::GenerateOffprings()
{
	unsigned long num_blocks;
	long double limit;
	if (auto sh_curPool = s_currMatingPool.lock()) {
		shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
		num_blocks = mig_ptr->GetBlocks()->size();
		limit = mig_ptr->GetProperties()->g_KBforMig;
		CrossImplement(sh_curPool, num_blocks, limit);
	}
}

shared_ptr<vector<shared_ptr<GA_Chromosome>>> GA_Crossover::GetNewGeneration()
{
	return s_newGeneration;
}
