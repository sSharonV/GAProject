#include "GA_Evolution.h"

GA_Evolution::GA_Evolution()
{
	GA_Migration* mig_ptr = new GA_Migration();
	mig_ptr = GA_Migration::GetCurInstance();
	unsigned long i = 0;

	// Initialize mapping from indexes to block_sn
	for (auto it : mig_ptr->GetBlocks()) {
		indexes_to_keys[i] = it.second.GetSN();
		i++;
	}
}

GA_Evolution* GA_Evolution::GetCurInstance()
{
	static GA_Evolution *m_evoInstance;
	if (!m_evoInstance) {
		m_evoInstance = new GA_Evolution();
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
	
	//m_popu = new GA_Population(10);

	
	
	// Initialize mapping from block_sn to indexes
	for (auto it : indexes_to_keys) {
		keys_to_indexes[it.second] = it.first;
	}
	printf("Hey");
}

/*
	StartEvolution() takes care of generating initial population
	-	Consists of chromosomes which generates by a random attachment of blocks to a chromosome,
		up to a given size by the user
*/
void GA_Evolution::StartEvolution()
{
	//m_popu->Initialize();

}

GA_Evolution * GetCurEvoInstance()
{
	return nullptr;
}
