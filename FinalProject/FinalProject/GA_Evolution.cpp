#include "GA_Evolution.h"

GA_Evolution::GA_Evolution()
{
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	unsigned long i = 0;

	// Initialize mapping from indexes to block_sn
	for (auto it : *(mig_ptr->GetBlocks())) {
		indexes_to_keys[i] = it.second->GetSN();
		i++;
	}

	// Initialize mapping from block_sn to indexes
	for (auto it : indexes_to_keys) {
		keys_to_indexes[it.second] = it.first;
	}
}

shared_ptr<GA_Evolution> GA_Evolution::GetCurInstance()
{
	static shared_ptr<GA_Evolution> m_evoInstance;
	if (!m_evoInstance) m_evoInstance = make_shared<GA_Evolution>(GA_Evolution());
	return	m_evoInstance;
}

map<unsigned long, string> GA_Evolution::GetInToKe()
{
	return indexes_to_keys;
}

map<string, unsigned long> GA_Evolution::GetKeToIn()
{
	return keys_to_indexes;
}

shared_ptr<GA_Population> GA_Evolution::GetCurPopulation()
{
	return m_popu;
}

void GA_Evolution::InitEvolution()
{
	// Retrieve population size which was supllied by the GUI
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	int pop_size = mig_ptr->GetProperties()->g_population_size;

	// Initialize shared_ptr to handle the population
	m_popu = make_shared<GA_Population>(GA_Population(pop_size));
}

/*
	StartEvolution() takes care of generating initial population
	-	Consists of chromosomes which generates by a random attachment of blocks to a chromosome,
		up to a given size by the user
*/
void GA_Evolution::StartEvolution()
{
	m_popu->Initialize();
	GA_SelectionTS selection(Selection::lin_rank_sel, 2);
	selection.InitMatingPool(m_popu);
	shared_ptr<GA_Population> currPool = make_shared<GA_Population>(GA_Population());
	currPool = selection.GetCurrentPool();
	GA_CrossoverU crossover(currPool, Crossover::one_point_cro);
	crossover.GenerateOffprings();
	GA_Mutation mutation(Mutation::uni_point_mut, crossover.GetNewGeneration(), 100);
	mutation.PerformMutation();
	printf("Hey");
}

