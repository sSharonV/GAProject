#include "GA_Evolution.h"

GA_Evolution::GA_Evolution()
{
	InitEvolution();
}

GA_Evolution* GA_Evolution::GetCurInstance()
{
	if (!m_evoInstance) {
		m_evoInstance = new GA_Evolution();
		return m_evoInstance;
	}
	return m_evoInstance;
}

map<unsigned long, string> GA_Evolution::GetInToKe()
{
	return indexes_to_keys;
}

map<string, unsigned long> GA_Evolution::GetKeToIn()
{
	return keys_to_indexes;
}

void GA_Evolution::InitEvolution()
{
	GA_Migration *mig_ptr = GA_Migration::GetCurInstance();
	unsigned long i = 0;

	// TODO: add GUI component to handle size of population
	m_popu = new GA_Population(10);

	// Initialize mapping from indexes to block_sn
	for (auto it : mig_ptr->GetBlocks()) {
		indexes_to_keys[i] = it.second.GetSN();
		i++;
	}

	// Initialize mapping from block_sn to indexes
	for (auto it : indexes_to_keys) {
		keys_to_indexes[it.second] = it.first;
	}
}

/*
	StartEvolution() takes care of generating initial population
	-	Consists of chromosomes which generates by a random attachment of blocks to a chromosome,
		up to a given size by the user
*/
void GA_Evolution::StartEvolution()
{
	m_popu->Initialize();

}
