#include "GA_Chromosome.h"
/*
GA_Chromosome::GA_Chromosome(unsigned long limit) : g_solLimit(limit)
{
	g_solution = vector<bool>(GA_Migration::GetCurInstance()->GetBlocks().size());
}

unsigned long GA_Chromosome::getSizeInBytes()
{
	return g_solSize;
}


void GA_Chromosome::setSizeInBytes(unsigned long s)
{
	g_solSize = s;
}


	InitSolution() takes care of initializing chromosome with feasible solution
	-	The solution stand the user requierments for migration size
	-	Chromosome has map of it's pointed blocks

void GA_Chromosome::InitSolution()
{
	// pointer to GA_Migration/GA_Evolution - for pulling information
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	shared_ptr<GA_Evolution> evo_ptr(GA_Evolution::GetCurInstance());

	// Reference to bipartite-graph
	map<string, Ded_Block> t_blocks = mig_ptr->GetBlocks();
	map<string, Ded_File> t_files = mig_ptr->GetFiles();

	// Copy map of indexes to block_sn
	map<unsigned long, string> t_indexes = evo_ptr->GetInToKe();
	map<string, unsigned long> t_sns = evo_ptr->GetKeToIn();

	chrono::duration<double> elapsed;
	const int interval = 60;
	unsigned long curr_size = 0;
	bool stop_attach = false;

	// Random protocol
	unsigned long i_rand;
	srand(time(NULL));
	auto start = chrono::high_resolution_clock::now();
	//	Stage 1 - Start attaching blocks up to the size of the limit
	do {
		// Get random block
		
		i_rand = rand() % t_blocks.size();
		string b_key = t_indexes[i_rand];
		Ded_Block* tb = &t_blocks[b_key];

		// for blocks that are not already included in the solution
		if (!g_solution.at(i_rand)) {	
			// if the current block can be attached to stage 1
			if (g_solSize + tb->GetSize() < g_solLimit) {
				g_solution.at(i_rand) = true;			// TMark the block as migrating
				g_blocks[i_rand] = tb;					// Update chromosome's map to include this neighboor
				g_solSize += tb->GetSize();				// Update chromosome's current size 
				if (g_solSize + mig_ptr->GetMinBlockSize() > g_solLimit) {
					stop_attach = true;
				}
			}
			if (curr_size == g_solSize) {				// For some reason the solution wasn't updated yet...
				auto curr = chrono::high_resolution_clock::now();
				elapsed = curr - start;
				// Check if after 60 seconds there's reason to terminate
				if (elapsed.count() > interval) {
					stop_attach = true;
				}
			}
			else {										// If g_solSize was updated - update start time for interval check....
				start = chrono::high_resolution_clock::now();
				curr_size = g_solSize;
			}	
		}
	} while (g_solSize < g_solLimit && !stop_attach);

	// Stage 2 - Add neighboors of the initial blocks
	for (auto it_blocks : g_blocks) {											// For each initial block
		unsigned long i;
		map<string, Ded_Block*> t_blocks = it_blocks.second->GetMyNeighboors();	// Retrive it's neighboors
		for (auto it_n_neigh : t_blocks) {										// For each neighboor...
			i = t_sns[it_n_neigh.first];			// Retrieve index of the sn (neighboor)

			//	for blocks that are not already included in the solution
			if (g_blocks.find(i) == g_blocks.end()) {
				g_solution.at(i) = true;			//	Mark the block as migrating
				g_blocks[i] = it_n_neigh.second;	// Update chromosome's map to include this neighboor
				g_solSize += g_blocks[i]->GetSize();			// Update chromosome's current size 
			}
		}
	}
}
*/