#include "GA_Mutation.h"

GA_Mutation::GA_Mutation(Mutation mut, int chance) : s_mut_mode(mut), s_mut_chance(chance)
{
	
}

GA_Mutation::~GA_Mutation()
{
	/*if (s_newGen.expired())
		s_newGen.reset();*/
}

void GA_Mutation::PerformMutation(shared_ptr<vector<shared_ptr<GA_Chromosome>>> newGen)
{
	unsigned long num_blocks;
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	num_blocks = mig_ptr->GetBlocks()->size();
	auto it = newGen->begin();
	for (int i = 0; i < mig_ptr->GetProperties()->g_elit_best; i++)
		it++;

	for (it; it != newGen->end(); it++) {
		switch (s_mut_mode) {
			case Mutation::sin_point_mut: {
				PerformSingle(*it);
				break;
			}
			case Mutation::uni_point_mut: {
				PerformUniform(*it);
				break;
			}
		}
	}
}

void GA_Mutation::PerformSingle(shared_ptr<GA_Chromosome> toMut)
{
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());

	// Random protocol
	unsigned long i_rand;
	int rand_chance;
	srand(time(NULL));

	rand_chance = rand() % 100 + 1;
	i_rand = rand() % (mig_ptr->GetBlocks()->size());

	if(rand_chance <= s_mut_chance)
		toMut->SetIndex(i_rand, !(toMut->CheckIndex(i_rand)));
}

void GA_Mutation::PerformUniform(shared_ptr<GA_Chromosome> toMut)
{
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());

	// Random protocol
	unsigned long distance;
	unsigned long relative;
	int rand_chance;
	srand(time(NULL));

	relative = mig_ptr->GetBlocks()->size() / 10;	// 10% of the number of blocks

	distance = rand() % (mig_ptr->GetBlocks()->size() - relative);	//	avoiding indexes which will bounce the limits

	for (unsigned long j = distance; j < distance + relative; j++) {
		rand_chance = rand() % 100 + 1;
		if(rand_chance <= s_mut_chance)
			toMut->SetIndex(j, !(toMut->CheckIndex(j)));
	}
}
