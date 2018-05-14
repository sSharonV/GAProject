#include "GA_Crossover.h"

GA_CrossoverTP::GA_CrossoverTP(shared_ptr<GA_Population> cur_pool, Crossover cros) : GA_Crossover(cur_pool, cros)
{

}

void GA_CrossoverTP::CrossImplement(shared_ptr<GA_Population> sh_pop, unsigned long num_blocks, long double limit)
{
	unsigned long i = 0;
	unsigned long border1, border2;
	do {
		chromo_1 = sh_pop->GetChromosomes()->at(i);
		chromo_2 = sh_pop->GetChromosomes()->at(i + 1);

		offspring_1 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i));
		offspring_2 = make_shared<GA_Chromosome>(GA_Chromosome(num_blocks, limit, i + 1));

		if (num_blocks < 3) {	//	Special cases to handle...
			if (num_blocks == 2) {
				offspring_1->SetIndex(0, chromo_2->CheckIndex(0));
				offspring_2->SetIndex(0, chromo_1->CheckIndex(0));
				offspring_1->SetIndex(1, chromo_2->CheckIndex(1));
				offspring_2->SetIndex(1, chromo_1->CheckIndex(1));
			}
			if (num_blocks == 1) {
				offspring_1->SetIndex(0, chromo_2->CheckIndex(0));
				offspring_2->SetIndex(0, chromo_1->CheckIndex(0));
			}
		}
		else {
			// Same amount of cells out of both borders
			border1 = num_blocks / 3;
			border2 = num_blocks - border1;

			//	Start with copying the original information from the attached parent - up to the border1
			for (unsigned long j = 0; j < border1; j++) {
				offspring_1->SetIndex(j, chromo_1->CheckIndex(j));
				offspring_2->SetIndex(j, chromo_2->CheckIndex(j));
			}
			//	Swap the information of the parents between the children - from the border1 
			for (unsigned long j = border1; j < border2; j++) {
				offspring_1->SetIndex(j, chromo_2->CheckIndex(j));
				offspring_2->SetIndex(j, chromo_1->CheckIndex(j));
			}
			//	Keep copying the original information from the attached parent
			for (unsigned long j = border2; j < num_blocks; j++) {
				offspring_1->SetIndex(j, chromo_1->CheckIndex(j));
				offspring_2->SetIndex(j, chromo_2->CheckIndex(j));
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

