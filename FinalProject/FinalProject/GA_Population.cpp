#include "GA_Population.h"

GA_Population::GA_Population(int size) : p_size(size) {
	p_chromosomes = make_shared<vector<shared_ptr<GA_Chromosome>>>(vector<shared_ptr<GA_Chromosome>>());
}

bool GA_Population::Initialize()
{
	// Retrieve the final size (Bytes) for migration
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	long double sol_size= mig_ptr->GetProperties()->g_KBforMig;
	unsigned long blocks_size = mig_ptr->GetBlocks()->size();

	shared_ptr<GA_Chromosome> t_chromo;

	int i = 0;
	for (i; i < p_size; i++) {
		// Initialize chromosome with solution size that was given by the user
		t_chromo = make_shared<GA_Chromosome>(GA_Chromosome(blocks_size, sol_size));
		t_chromo->InitSolution();
		p_chromosomes->push_back(t_chromo);
	}
	return false;
}
