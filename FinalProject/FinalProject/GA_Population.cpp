#include "GA_Population.h"

GA_Population::GA_Population(int size) : p_size(size) {
	p_chromosomes = make_shared<vector<shared_ptr<GA_Chromosome>>>(vector<shared_ptr<GA_Chromosome>>(0));
}

GA_Population::GA_Population(vector<shared_ptr<GA_Chromosome>> chromosomes)
{
	p_size = chromosomes.size();
	p_chromosomes = make_shared<vector<shared_ptr<GA_Chromosome>>>(vector<shared_ptr<GA_Chromosome>>(chromosomes));
}

GA_Population::GA_Population()
{
	p_chromosomes = make_shared<vector<shared_ptr<GA_Chromosome>>>(vector<shared_ptr<GA_Chromosome>>(0));
}

shared_ptr<vector<shared_ptr<GA_Chromosome>>> GA_Population::GetChromosomes()
{
	return p_chromosomes;
}

void GA_Population::Initialize()
{
	// Retrieve the final size (Bytes) for migration
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	long double sol_size= mig_ptr->GetProperties()->g_KBforMig;
	unsigned long blocks_size = mig_ptr->GetBlocks()->size();

	shared_ptr<GA_Chromosome> t_chromo;

	int i = 0;
	for (i; i < p_size; i++) {
		// Initialize chromosome with solution size that was given by the user
		t_chromo = make_shared<GA_Chromosome>(GA_Chromosome(blocks_size, sol_size, i));
		t_chromo->InitSolution();
		p_chromosomes->push_back(t_chromo);
	}
}

void GA_Population::InitBySelect(shared_ptr<GA_Chromosome> push_chr)
{
	p_chromosomes->push_back(push_chr);
}

int GA_Population::GetPopSize()
{
	return p_size;
}
