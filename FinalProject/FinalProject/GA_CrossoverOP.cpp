#include "GA_Crossover.h"

GA_CrossoverOP::GA_CrossoverOP(shared_ptr<GA_Population> cur_pool, Crossover cros) : GA_Crossover(cur_pool, cros)
{
}

void GA_CrossoverOP::CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit)
{
	unsigned long i = 0;
	unsigned long border;
	do {
		chromo_1 = sh_pop->GetChromosomes()->at(i);
		chromo_2 = sh_pop->GetChromosomes()->at(i + 1);

		offspring_1 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i));
		offspring_2 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i + 1));

		if (num_blocks < 2) {	// Case of only one block for cross-overing...
			offspring_1->SetIndex(0, chromo_2->CheckIndex(0));
			offspring_2->SetIndex(0, chromo_1->CheckIndex(0));
		}
		else {
			border = num_blocks / 2;	// border will be at the middle of a chromosome

										//	Start with copying the original information from the attached parent - up to the border
			for (unsigned long j = 0; j < border; j++) {
				offspring_1->SetIndex(j, chromo_1->CheckIndex(j));
				offspring_2->SetIndex(j, chromo_2->CheckIndex(j));
			}

			//	Swap the information of the parents between the children - from the border
			for (unsigned long j = border; j < num_blocks; j++) {
				offspring_1->SetIndex(j, chromo_2->CheckIndex(j));
				offspring_2->SetIndex(j, chromo_1->CheckIndex(j));
			}
		}
		//offspring_1->AttachMyBlocks();
		//offspring_2->AttachMyBlocks();
		//	Adds the new children to the result population
		s_newGeneration->push_back(offspring_1);
		s_newGeneration->push_back(offspring_2);
		i += 2;
	} while (s_newGeneration->size() != sh_pop->GetPopSize());
}


