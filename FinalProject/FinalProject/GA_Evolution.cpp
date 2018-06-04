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

shared_ptr<GA_Population> GA_Evolution::GetMatingPool()
{
	return m_matingPool;
}

shared_ptr<GA_Population> GA_Evolution::GetInitialPopulation()
{
	return m_Initialpopu;
}

void GA_Evolution::SetMatingPool(GA_Population new_pop)
{
	m_matingPool = make_shared<GA_Population>(GA_Population(new_pop));
}

void GA_Evolution::InitEvolution()
{
	// Retrieve population size which was supllied by the GUI
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	int pop_size = mig_ptr->GetProperties()->g_population_size;

	// Initialize shared_ptr to handle the population
	m_popu = make_shared<GA_Population>(GA_Population(pop_size));
}

void GA_Evolution::StartEvolution()
{
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	shared_ptr<GA_Selection> selection;
	shared_ptr<GA_Crossover> crossover;
	shared_ptr<GA_Mutation> mutation;
	int curr_gen = 0;

	switch (mig_ptr->GetProperties()->g_sel_mode) {
	case Selection::rou_whe_sel: {
		selection.reset(new GA_SelectionRW(mig_ptr->GetProperties()->g_sel_mode, mig_ptr->GetProperties()->g_elit_best));
		break;
	}
	case Selection::lin_rank_sel: {
		selection.reset(new GA_SelectionLRB(mig_ptr->GetProperties()->g_sel_mode, mig_ptr->GetProperties()->g_elit_best));
		break;
	}
	case Selection::tour_sel: {
		selection.reset(new GA_SelectionTS(mig_ptr->GetProperties()->g_sel_mode, mig_ptr->GetProperties()->g_elit_best));
		break;
	}
	default: break;
	}

	switch (mig_ptr->GetProperties()->g_cros_mode) {
	case Crossover::one_point_cro: {
		crossover.reset(new GA_CrossoverOP(mig_ptr->GetProperties()->g_cros_mode));
		break;
	}
	case Crossover::two_point_cro: {
		crossover.reset(new GA_CrossoverTP(mig_ptr->GetProperties()->g_cros_mode));
		break;
	}
	case Crossover::uni_cro: {
		crossover.reset(new GA_CrossoverU(mig_ptr->GetProperties()->g_cros_mode));
		break;
	}
	default: break;
	}

	mutation = make_shared<GA_Mutation>(GA_Mutation(mig_ptr->GetProperties()->g_mut_mode, mig_ptr->GetProperties()->g_mut_rate));

	m_popu->Initialize();
	m_Initialpopu = make_shared<GA_Population>(GA_Population(*m_popu->GetChromosomes()));

	while(curr_gen != mig_ptr->GetProperties()->g_generations){
		
		selection->InitMatingPool(m_popu);

		crossover->GenerateOffprings(m_matingPool);
	
		mutation->PerformMutation(crossover->GetNewGeneration());

		for (auto it_chr : *(crossover->GetNewGeneration())) {
			it_chr->AttachMyBlocks();
			if (curr_gen + 1 == mig_ptr->GetProperties()->g_start_fix) {
				it_chr->FixToFeasibleSol();
			}
		}

		m_popu = make_shared<GA_Population>(GA_Population(*crossover->GetNewGeneration()));
		curr_gen++;
	}
	
	sort(m_popu->GetChromosomes()->begin(), m_popu->GetChromosomes()->end(),
		//	- Sort being processed with the objective function value of the chromosomes
		[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
		return o1->ObjectiveFunc() < o2->ObjectiveFunc();
	});

	sort(m_Initialpopu->GetChromosomes()->begin(), m_Initialpopu->GetChromosomes()->end(),
		//	- Sort being processed with the objective function value of the chromosomes
		[](const shared_ptr<GA_Chromosome> o1, const shared_ptr<GA_Chromosome> o2) {
		return o1->ObjectiveFunc() < o2->ObjectiveFunc();
	});
	
	printf("Hey");
}

