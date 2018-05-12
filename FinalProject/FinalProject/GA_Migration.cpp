#include "stdafx.h"
#include "GA_Migration.h"

//shared_ptr<GA_Migration> GA_Migration::m_migInstance = make_shared<GA_Migration>(GA_Migration());

GA_Migration::GA_Migration(){

	mig_props = make_shared<general_prop>();
	using t_blocks = map<string, shared_ptr<Ded_Block>>;
	using il_blocks = initializer_list<t_blocks::value_type>;
	using  t_files = map<string, shared_ptr<Ded_File>>;
	using il_files = initializer_list<t_files::value_type>;
	m_blocks =  make_shared<t_blocks>(il_blocks{});
	m_files = make_shared<t_files>(il_files{});
}

/*GA_Migration::~GA_Migration()
{
	//delete m_migInstance;
}*/

/*
GA_Migration::GA_Migration(const GA_Migration & other)
{
	m_blocks = other.GetBlocks();
}*/

void GA_Migration::InitBipartiteGraph(ifstream &input)
{
	using t_blocks = map<string, string>;
	using il_blocks = initializer_list<t_blocks::value_type>;
	using  t_files = map<string, vector<string>>;
	using il_files = initializer_list<t_files::value_type>;
	shared_ptr<map<string, string>> blocks_size = make_shared<t_blocks>(il_blocks{});;
	shared_ptr<map<string, vector<string>>> files_blocks = make_shared<t_files>(il_files{});;
	InitFileVector(input, blocks_size, files_blocks);
	InitBlockVector(input);
	ConnectBlockAndFiles(blocks_size, files_blocks);
}

long double GA_Migration::GetSolutionLimitSize()
{
	if ((mig_props)->trueFor_KB) {	// return the number of KB (10^3B)
		return (mig_props)->g_kb;
	}
	else {
		long double size;
		size = (long double)((mig_props)->g_totalKB) * ((mig_props)->g_percent);
		return size;
	}
}

long double GA_Migration::GetSystemSize()
{
	return mig_props->g_totalKB;
}

unsigned long GA_Migration::GetMinBlockSize()
{
	return m_min_block_size.second;
}

shared_ptr<map<string, shared_ptr<Ded_Block>>> GA_Migration::GetBlocks()
{
	return m_blocks;
}

shared_ptr<map<string, shared_ptr<Ded_File>>> GA_Migration::GetFiles()
{
	return m_files;
}

shared_ptr<general_prop> GA_Migration::GetProperties()
{
	return mig_props;
}

shared_ptr<GA_Migration> GA_Migration::GetCurInstance()
{
	static shared_ptr<GA_Migration> m_migInstance;
	if (!m_migInstance) m_migInstance = make_shared<GA_Migration>(GA_Migration());
	return	m_migInstance;
}

/*
SafeExit() clears the maps of blocks and files.
-	deletes the pointer to GA_Migration reference
-	shared_ptr getting initialized newly
*/
void GA_Migration::SafeExit()
{
	using t_blocks = map<string, shared_ptr<Ded_Block>>;
	using il_blocks = initializer_list<t_blocks::value_type>;
	using  t_files = map<string, shared_ptr<Ded_File>>;
	using il_files = initializer_list<t_files::value_type>;
	m_blocks = make_shared<t_blocks>(il_blocks{});
	m_files = make_shared<t_files>(il_files{});
	mig_props = make_shared<general_prop>();
}

void GA_Migration::InitKBForMig()
{

	// Updates the size properties according to its measurments
	switch (mig_props->g_eps_size)
	{
		case BytesMeasure::kilo: {
			mig_props->g_epsilon = (mig_props->g_epsilon)*(1024);
			break;
		}
		case BytesMeasure::mega: {
			mig_props->g_epsilon = (mig_props->g_epsilon)*(pow(1024,2));
			break;
		}
		case BytesMeasure::giga: {
			mig_props->g_epsilon = (mig_props->g_epsilon)*(pow(1024, 3));
			break;
		}
		default:
			break;
	}
	if (mig_props->trueFor_KB) {
		// Updates the size properties according to its measurments
		switch (mig_props->g_kb_size)
		{
		case BytesMeasure::kilo: {
			mig_props->g_kb = (mig_props->g_kb)*(1024);
			break;
		}
		case BytesMeasure::mega: {
			mig_props->g_kb = (mig_props->g_kb)*(pow(1024, 2));
			break;
		}
		case BytesMeasure::giga: {
			mig_props->g_kb = (mig_props->g_kb)*(pow(1024, 3));
			break;
		}
		default:
			break;
		}
		mig_props->g_KBforMig = (mig_props->g_epsilon + mig_props->g_kb);
		mig_props->g_KBforMig *= ((100 + mig_props->g_over_percent) / 100);
	}
	else {
		mig_props->g_KBforMig = mig_props->g_totalKB * ((mig_props->g_percent) / 100);
		mig_props->g_KBforMig *= ((100 + mig_props->g_over_percent) / 100);
	}
}

void GA_Migration::InitBlockVector(ifstream& input)
{
	string line;
	string block_sn, 
		   block_id, 
		   num_files;
	string file_sn;
	vector<string> b_props;
	unsigned long n_files, n_blocks;
	unsigned long i;
	bool main_flag = true, first = true;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the CSV-file
	while (main_flag) {
		i = 1;
		if (first) {
			b_props = InputHelper(input, "B,", n_blocks);
			first = false;
		}
		if (!first){
		// Next time it's get empty will be when we done processing blocks
			if(!b_props.empty()){
				block_sn = b_props.at(i++);
				block_id = b_props.at(i++);
				num_files = b_props.at(i++);
				n_files = stoul(num_files);
				shared_ptr<Ded_Block> temp(make_shared<Ded_Block>(Ded_Block(stoul(block_sn), block_id, n_files)));
				(*m_blocks)[block_sn] = temp;
				for (unsigned long j = 0; j < n_files; j++) {
					file_sn = b_props.at(i++);
					(*m_blocks)[block_sn]->AddFile((*m_files)[file_sn]);
				}
				if (m_blocks->size() != n_blocks)
					b_props = InputHelper(input, "B,", n_blocks);
				else b_props.clear();
			}
			else main_flag = false;
		}
	}
}

void GA_Migration::InitFileVector(ifstream & input, shared_ptr<map<string, string>> blocks, shared_ptr<map<string, vector<string>>> f_b) {
	string line;
	string file_sn,
		file_id,
		dir_sn,
		num_blocks;
	string block_sn,
		block_size;
	vector<string> f_props;
	bool main_flag = true, first = true;
	unsigned long n_blocks;
	unsigned long n_files;
	unsigned long i;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the CSV-file
	while (main_flag) {
		i = 1;
		if (first) {
			f_props = InputHelper(input, "F,", n_files);
			first = false;
		}
		if (!first) {
			// Next time it's get empty will be when we done processing files
			if (!f_props.empty()) {
				file_sn = f_props.at(i++);
				file_id = f_props.at(i++);
				dir_sn = f_props.at(i++);
				num_blocks = f_props.at(i++);
				n_blocks = stoul(num_blocks);
				shared_ptr<Ded_File> temp(make_shared<Ded_File>(Ded_File(stoul(file_sn), file_id, stoul(dir_sn), n_blocks)));
				(*m_files)[file_sn] = temp;
				for (unsigned long j = 0; j < n_blocks; j++) {
					block_sn = f_props.at(i++);
					block_size = f_props.at(i++);
					// Update helper hash-maps to later connect the bipartite-graph
					(*blocks)[block_sn] = block_size;
					(*f_b)[file_sn].push_back(block_sn);
				}
				if(m_files->size() != n_files)
					f_props = InputHelper(input, "F,", n_files);
				else f_props.clear();
			}
			else main_flag = false;
		}
	}
}

void GA_Migration::ConnectBlockAndFiles(shared_ptr<map<string, string>> block_sizes, shared_ptr<map<string, vector<string>>> f_b)
{
	for (auto it : *block_sizes) {				// for every block
														//	Update it size
		(*m_blocks)[it.first]->setBlockSize(stoi(it.second));
		(mig_props)->g_totalKB += stoi(it.second);		// Sum the size (in bytes) of all blocks
	}
	(mig_props)->g_totalKB /= (10 ^ 3);				// In KB
	for (auto it : *f_b) {					// for every file
		for (auto sub_it : it.second) {		// check associated blocks to it
													//	Update pointer to the reference of the associated blocks
			(*m_files)[it.first]->UpdateBlockSN((*m_blocks)[sub_it]);
		}
	}
	auto t_it = block_sizes->begin();
	unsigned long min = stoul(t_it->second);
	m_min_block_size.first = t_it->first;
	m_min_block_size.second = min;
	for (auto it : *block_sizes) {
		if (min > stoul(it.second)) {
			min = stoul(it.second);
			m_min_block_size.first = it.first;
			m_min_block_size.second = min;
		}
	}
}

/*
	Takes care of processing input
	-	return vector with strings - which are splits of inputted line
	-	initialize the number of blocks\files that are going to be processed
*/
vector<string> GA_Migration::InputHelper(ifstream &in, string to_search, unsigned long& num) {
	vector<string> result;
	string line; getline(in, line);
	stringstream lineStream(line);
	string cell;

	while (line.find(to_search) == string::npos) { 
		getline(in, line);
		if (line.find("Num files:") != string::npos && (to_search.compare("F,") == 0))
			num = stoul(line.substr(line.find(":") + 1));
		else if(line.find("Num blocks:") != string::npos && (to_search.compare("B,") == 0))
			num = stoul(line.substr(line.find(":") + 1));
	}	// Skip strings in start of file and update the reference of of 'num'
	lineStream.str(line);
	while (getline(lineStream, cell, ','))
		result.push_back(cell);
	return result;
}

void GA_Migration::RunGeneticAlgo()
{
	InitKBForMig();
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
	ga_evo->InitEvolution();
	ga_evo->StartEvolution();
}


