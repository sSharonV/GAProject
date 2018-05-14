#include "GA_Crossover.h"

GA_CrossoverU::GA_CrossoverU(shared_ptr<GA_Population> cur_pool, Crossover cros) : GA_Crossover(cur_pool, cros)
{
}

void GA_CrossoverU::CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit)
{
	unsigned long i = 0;
	unsigned long j = 0;
	// Random protocol
	unsigned long i_rand;
	srand(time(NULL));
	do {
		i = 0;

		chromo_1 = sh_pop->GetChromosomes()->at(j);
		chromo_2 = sh_pop->GetChromosomes()->at(j + 1);

		offspring_1 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i));
		offspring_2 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i + 1));
		while (i != num_blocks) {	//	Crossing data across vector length
			//	Generate boolean values for some random mask
			i_rand = rand() % 2;
			if (i_rand) {	// Swap data
				offspring_1->SetIndex(i, chromo_2->CheckIndex(i));
				offspring_2->SetIndex(i, chromo_1->CheckIndex(i));
			}
			else {
				offspring_1->SetIndex(i, chromo_1->CheckIndex(i));
				offspring_2->SetIndex(i, chromo_2->CheckIndex(i));
			}
			i++;
		}
		//offspring_1->AttachMyBlocks();
		//offspring_2->AttachMyBlocks();
		//	Adds the new children to the result population
		s_newGeneration->push_back(offspring_1);
		s_newGeneration->push_back(offspring_2);
		j += 2;
	} while (s_newGeneration->size() != sh_pop->GetPopSize());
}
