#include "GA_Population.h"

GA_Population::GA_Population(int size) : p_size(size) {}

bool GA_Population::Initialize()
{
	// const pointer to GA_Migration - for pulling information
	GA_Migration *mig_ptr = GA_Migration::GetCurInstance();

	int i = 0;
	for (i; i < p_size; i++) {
		// Initialize chromosome with solution size that was given by the user
		/* 
			TODO: Handle diffrent approches, including other properties,
				  to determine the size of solution
		*/
		GA_Chromosome *chromo = new GA_Chromosome(mig_ptr->GetProperties().g_kb);

		// chromo is an chromosome which 
		chromo->InitSolution();

		
	}
	return false;
}
