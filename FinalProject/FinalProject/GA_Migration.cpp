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

void GA_Migration::SetGeneralProperties(general_prop &properties)
{
	(mig_props)->g_sel_mode = properties.g_sel_mode;
	(mig_props)->g_cros_mode = properties.g_cros_mode;
	(mig_props)->g_mut_mode = properties.g_mut_mode;
	(mig_props)->g_population_size = properties.g_population_size;
	(mig_props)->g_over_percent = properties.g_over_percent;
	(mig_props)->g_generations = properties.g_generations;
	(mig_props)->g_elit_best = properties.g_elit_best;
	(mig_props)->g_start_fix = properties.g_start_fix;
	(mig_props)->g_epsilon = properties.g_epsilon;
	(mig_props)->g_eps_size = properties.g_eps_size;
	(mig_props)->trueFor_KB = properties.trueFor_KB;
	if ((mig_props)->trueFor_KB) {
		(mig_props)->g_kb = properties.g_kb;
		(mig_props)->g_kb_size = properties.g_kb_size;
	}
	else (mig_props)->g_percent = properties.g_percent;
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

general_prop GA_Migration::GetProperties()
{
	return *mig_props;
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
-	shared_ptr
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
	string block_sn, block_id, num_files;
	string file_sn;
	int n_files;
	unsigned long length = 0, last_length = 0;
	bool main_flag = true, flag = false;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the textf=file
	while (main_flag) {
		getline(input, line);
		if (line.find("B,") == string::npos) {		 // save the position of the files
			last_length = length;					// position of start of line
			length = (unsigned long)(input.tellg());					// position of end of line
		}
		else {
			//input.seekg(last_length);
			input.seekg(180694); //180694[ths=0.1], 451660[ths=1]	// TODO: find the right combination to start from.
			length = (unsigned long)(input.tellg());
			flag = true;
			while (IsFirstChar(input, 'B') && flag) {	 // start processing the files
				//input.seekg(length - 91 + 2);			 
				input.seekg(length+2);
				block_sn = InputHelper(input);
				block_id = InputHelper(input);
				num_files = InputHelper(input);
				n_files = stoi(num_files);

				shared_ptr<Ded_Block> temp(make_shared<Ded_Block>(Ded_Block(stoi(block_sn), block_id, n_files)));
				(*m_blocks)[block_sn] = temp;
				for (int i = 0; i < n_files; i++) {
					file_sn = InputHelper(input);
					(*m_blocks)[block_sn]->AddFile((*m_files)[file_sn]);
				}
				length = (unsigned long)(input.tellg());
				length++;
			}
		}
		if (flag) main_flag = false;
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
	bool main_flag = true, flag = true;
	int n_blocks;
	unsigned long length;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the textf=file
	while (main_flag) {
		getline(input, line);
		if ((line).find("F,") == string::npos)		 // save the position of the files
			length = (unsigned long)(input.tellg());
		else {
			while (IsFirstChar(input, 'F') || flag) {	 // start processing the files
				if (flag) {
					input.seekg(length - 8);					// start at the beggining of the file sequence
					length = (unsigned long)(input.tellg());
					flag = false;
				}
				else {
					length = (unsigned long)(input.tellg());
					input.seekg(length + 3);
				}
				file_sn = InputHelper(input);
				file_id = InputHelper(input);
				dir_sn = InputHelper(input);
				num_blocks = InputHelper(input);
				n_blocks = stoul(num_blocks);
				shared_ptr<Ded_File> temp(make_shared<Ded_File>(Ded_File(stoul(file_sn), file_id, stoul(dir_sn), n_blocks)));
				//string fsn = file_sn;
				(*m_files)[file_sn] = temp;
				for (int i = 0; i < n_blocks; i++) {
					block_sn = InputHelper(input);
					block_size = InputHelper(input);
					// Update helper hash-maps to later connect the bipartite-graph
					(*blocks)[block_sn] = block_size;
					(*f_b)[file_sn].push_back(block_sn);
				}
			}
		}
		if (!flag) main_flag = false;
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

bool GA_Migration::IsFirstChar(ifstream & in, char ch)
{
	char c;
	unsigned long cur_pos = (unsigned long)(in.tellg());
	in >> c;
	in.seekg(cur_pos);
	if (c == ch) return true;
	else return false;
}

string GA_Migration::InputHelper(ifstream &in)
{
	char ch;
	string word;
	while (in >> ch) {
		if (ch == ',')
			return word;
		else
			word.append(1, ch);
	}
	return NULL;
}

void GA_Migration::RunGeneticAlgo()
{
	InitKBForMig();
	/*
	shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
	ga_evo->InitEvolution();
	ga_evo->StartEvolution();
	*/
}


