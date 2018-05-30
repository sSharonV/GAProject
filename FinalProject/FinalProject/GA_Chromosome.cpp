#include "GA_Chromosome.h"
#include <iterator>

GA_Chromosome::GA_Chromosome(unsigned long num_blocks, long double limit, int id) : g_solLimit(limit), g_id(id)
{
	using t_blocks = map<unsigned long, weak_ptr<Ded_Block>>;
	using il_blocks = initializer_list<t_blocks::value_type>;
	g_blocks = make_shared<t_blocks>(il_blocks{});
	g_solution = make_shared<vector<bool>>(vector<bool>(num_blocks));
	g_solSize = 0;
}

GA_Chromosome::GA_Chromosome(const GA_Chromosome & other)
{
	this->g_solSize = other.g_solSize;
	this->g_solLimit = other.g_solLimit;
	this->g_blocks = other.g_blocks;
	this->g_solution = other.g_solution;
	this->g_id = other.g_id;
}

GA_Chromosome::~GA_Chromosome()
{
}

/*
bool GA_Chromosome::operator<(GA_Chromosome& const other) const
{
	return (ObjectiveFunc() < other.ObjectiveFunc()) ? true : false ;
}*/

long double GA_Chromosome::ObjectiveFunc() const
{
	return ((g_solSize-g_solLimit) > 0) ? (g_solSize - g_solLimit)
										: 0.0;
}

void GA_Chromosome::setSizeInBytes(long double s)
{
	g_solSize = s;
}

/*
	InitSolution() takes care of initializing chromosome with feasible solution
	-	The solution stand the user requierments for migration size
	-	Chromosome has map of it's pointed blocks
*/
void GA_Chromosome::InitSolution()
{
	// pointer to GA_Migration/GA_Evolution - for pulling information
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	shared_ptr<GA_Evolution> evo_ptr(GA_Evolution::GetCurInstance());

	// Reference to bipartite-graph
	shared_ptr<map<string, shared_ptr<Ded_Block>>> t_blocks = mig_ptr->GetBlocks();
	shared_ptr<map<string, shared_ptr<Ded_File>>> t_files = mig_ptr->GetFiles();

	// Copy map of indexes to block_sn
	map<unsigned long, string> t_indexes = evo_ptr->GetInToKe();
	map<string, unsigned long> t_sns = evo_ptr->GetKeToIn();

	chrono::duration<double> elapsed;
	const int interval = mig_ptr->GetProperties()->g_timeOut;
	long double curr_size = 0;
	bool stop_attach = false;

	// Random protocol
	unsigned long i_rand;
	srand(time(NULL));

	auto start = chrono::high_resolution_clock::now();

	//	Stage 1 - Start attaching blocks up to the size of the limit (with minimal size which was calculated..)
	do {
		// Get random block
		i_rand = rand() % t_blocks->size();
		string b_key = t_indexes[i_rand];
		shared_ptr<Ded_Block> tb;
		tb = t_blocks->find(b_key)->second;

		// for blocks that are not already included in the solution
		if (!(g_solution)->at(i_rand)) {
			// if the current block can be attached to stage 1
			if (g_solSize + tb->GetSize() < g_solLimit) {
				g_solution->at(i_rand) = true;			// TMark the block as migrating
				(*g_blocks)[i_rand] = tb;		// Update chromosome's map to include this neighboor
				g_solSize += tb->GetSize();				    // Update chromosome's current size 	
			}
			if (g_solSize + mig_ptr->GetMinBlockSize() > g_solLimit) {
				stop_attach = true;
			}
		}
		if (curr_size == g_solSize) {					// For some reason the solution wasn't updated yet...
			auto curr = chrono::high_resolution_clock::now();
			elapsed = curr - start;
			// Check if after 'interval' seconds there's reason to terminate
			if (elapsed.count() > interval) {
				stop_attach = true;
			}
		}
		else {											// If g_solSize was updated - update start time for interval check....
			start = chrono::high_resolution_clock::now();
			curr_size = g_solSize;
		}
	} while ((g_solSize < g_solLimit || g_solSize < mig_ptr->GetProperties()->g_KB_minimal) && !stop_attach);

	g_migratedSize = g_solSize;

	// Stage 2 - Add neighboors of the initial blocks
	FixToFeasibleSol();
}

shared_ptr<map<unsigned long, weak_ptr<Ded_Block>>> GA_Chromosome::GetMyBlocks()
{
	return g_blocks;
}

void GA_Chromosome::FixToFeasibleSol() {
	shared_ptr<GA_Evolution> evo_ptr(GA_Evolution::GetCurInstance());
	map<string, unsigned long> t_sns = evo_ptr->GetKeToIn();
	for (auto it_blocks : *g_blocks) {											// For each initial block
		unsigned long i;
		if (auto sh_b = it_blocks.second.lock()) {
			shared_ptr<map<string, weak_ptr<Ded_Block>>> t_blocks = sh_b->GetMyNeighboors();					// Retrive it's neighboors
			for (auto it_n_neigh : *t_blocks) {										// For each neighboor...
				if (auto sh_n = it_n_neigh.second.lock()) {
					i = t_sns[sh_n->GetSN()];			// Retrieve index of the sn (neighboor)
														//	for blocks that are not already included in the solution
					if (g_blocks->find(i) == g_blocks->end()) {
						g_solution->at(i) = true;			//	Mark the block as migrating
						(*g_blocks)[i] = it_n_neigh.second;	// Update chromosome's map to include this neighboor
						g_solSize += (sh_n->GetSize());			// Update chromosome's current size 
					}
				}
			}
		}
	}
}

void GA_Chromosome::AttachMyBlocks()
{
	// pointer to GA_Migration/GA_Evolution - for pulling information
	shared_ptr<GA_Migration> mig_ptr(GA_Migration::GetCurInstance());
	shared_ptr<GA_Evolution> evo_ptr(GA_Evolution::GetCurInstance());

	// Reference to bipartite-graph
	shared_ptr<map<string, shared_ptr<Ded_Block>>> t_blocks = mig_ptr->GetBlocks();
	shared_ptr<map<string, shared_ptr<Ded_File>>> t_files = mig_ptr->GetFiles();

	// Copy map of indexes to block_sn
	map<unsigned long, string> t_indexes = evo_ptr->GetInToKe();
	map<string, unsigned long> t_sns = evo_ptr->GetKeToIn();

	// Iterate the boolean vector for migrating blocks
	for (unsigned long i = 0; i < g_solution->size(); i++){
		if (g_solution->at(i)) {	// block we need to assign to the chromosome's vector
			string it_key = t_indexes[i];							//	Retrieve key of the current index
			if (g_blocks->find(i) == g_blocks->end()) {				// If the block isn't included
				(*g_blocks)[i] = (t_blocks->find(it_key))->second;		//	Retrieve the reference of a block
				g_solSize += (t_blocks->find(it_key))->second->GetSize();		//	Updating the size of this solution
			}
		}
	}
}

bool GA_Chromosome::CheckIndex(unsigned long index)
{
	return g_solution->at(index);
}

void GA_Chromosome::SetIndex(unsigned long index, bool val)
{
	g_solution->at(index) = val;
}

long double GA_Chromosome::GetSolSize()
{
	return g_solSize;
}

long double GA_Chromosome::GetMigSize()
{
	return g_migratedSize;
}
