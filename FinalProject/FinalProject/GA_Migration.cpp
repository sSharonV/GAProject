#include "stdafx.h"
#include "GA_Migration.h"

GA_Migration::GA_Migration(){}

void GA_Migration::InitBipartiteGraph(ifstream &input)
{
	map<string, string> blocks_size;
	map<string, vector<string>> files_blocks;
	InitFileVector(input, blocks_size, files_blocks);
	InitBlockVector(input);
	ConnectBlockAndFiles(blocks_size, files_blocks);
	// free the hash-maps memmory - size = 0
	blocks_size.clear();
	files_blocks.clear();
}

void GA_Migration::SetGeneralProperties(general_prop &properties)
{
	mig_props.g_sel_mode = properties.g_sel_mode;
	mig_props.g_cros_mode = properties.g_cros_mode;
	mig_props.g_mut_mode = properties.g_mut_mode;
	mig_props.g_over_percent = properties.g_over_percent;
	mig_props.g_generations = properties.g_generations;
	mig_props.g_elit_best = properties.g_elit_best;
	mig_props.g_start_fix = properties.g_start_fix;
	mig_props.g_epsilon = properties.g_epsilon;
	mig_props.trueFor_KB = properties.trueFor_KB;
	if (mig_props.trueFor_KB) mig_props.g_kb = properties.g_kb;
	else mig_props.g_percent = properties.g_percent;
}

unsigned long GA_Migration::GetSolutionLimitSize()
{
	if (mig_props.trueFor_KB) {	// return the number of KB (10^3B)
		return mig_props.g_kb;
	}
	else {
		long double size;
		size = (mig_props.g_totalKB) * (mig_props.g_percent);
		return size;
	}
}

GA_Migration* GA_Migration::GetCurInstance()
{
	if (!m_migInstance) 
		return new GA_Migration();
	return m_migInstance;
}

void GA_Migration::SafeExit()
{
	m_blocks.clear();
	m_files.clear();
	this->DeleteCurInstance();
}

void GA_Migration::DeleteCurInstance()
{
	delete m_migInstance;
}

void GA_Migration::InitBlockVector(ifstream& input)
{
	string line;
	char ch;
	string block_sn, block_id, num_files;
	string file_sn;
	int n_files;
	int length = 0, last_length = 0;
	bool main_flag = true, flag = false;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the textf=file
	while (main_flag) {
		getline(input, line);
		if (line.find("B,") == string::npos) {		 // save the position of the files
			last_length = length;					// position of start of line
			length = input.tellg();					// position of end of line
		}
		else {
			//input.seekg(last_length);
			input.seekg(180694); //180694[ths=0.1], 451660[ths=1]	// TODO: find the right combination to start from.
			length = input.tellg();
			flag = true;
			while (IsFirstChar(input, 'B') && flag) {	 // start processing the files
				//input.seekg(length - 91 + 2);			 
				input.seekg(length+2);
				block_sn = InputHelper(input);
				block_id = InputHelper(input);
				num_files = InputHelper(input);
				n_files = stoi(num_files);
				m_blocks[block_sn] = Ded_Block(stoi(block_sn), block_id, n_files);
				for (int i = 0; i < n_files; i++) {
					file_sn = InputHelper(input);
					m_blocks[block_sn].AddFile(m_files[file_sn]);
				}
				length = input.tellg();
				length++;
			}
		}
		if (flag) main_flag = false;
	}
}

void GA_Migration::InitFileVector(ifstream& input, map<string, string>& blocks, map<string, vector<string>>& f_b)
{
	string line;
	string file_sn, file_id, dir_sn, num_blocks;
	string block_sn, block_size;
	char ch;
	bool main_flag = true, flag = true;
	int n_blocks;
	int length;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the textf=file
	while (main_flag) {
		getline(input, line);
		if (line.find("F,") == string::npos)		 // save the position of the files
			length = input.tellg();
		else {
			while (IsFirstChar(input, 'F') || flag) {	 // start processing the files
				if (flag) {
					input.seekg(length - 8);					// start at the beggining of the file sequence
					length = input.tellg();
					flag = false;
				}
				else {
					length = input.tellg();
					input.seekg(length + 3);
				}
				file_sn = InputHelper(input);
				file_id = InputHelper(input);
				dir_sn = InputHelper(input);
				num_blocks = InputHelper(input);
				n_blocks = stoul(num_blocks);
				m_files[file_sn] = Ded_File(stoul(file_sn), file_id, stoul(dir_sn), n_blocks);
				if (file_sn.compare("2597") == 0) { 
					ch = ' ';
				}
				for (int i = 0; i < n_blocks; i++) {
					block_sn = InputHelper(input);
					block_size = InputHelper(input);
					// Update helper hash-maps to later connect the bipartite-graph
					blocks[block_sn] = block_size;
					f_b[file_sn].push_back(block_sn);
				}
			}
		}
		if (!flag) main_flag = false;
	}
}

void GA_Migration::ConnectBlockAndFiles(map<string, string> &block_sizes, map<string, vector<string>> &f_b)
{
	for(auto const& it : block_sizes){				// for every block
		//	Update it size
		m_blocks[it.first].setBlockSize(stoi(it.second));
		mig_props.g_totalKB += stoi(it.second);		// Sum the size (in bytes) of all blocks
	}
	mig_props.g_totalKB /= (10 ^ 3);				// In KB
	for (auto const& it : f_b) {					// for every file
		for (auto const& sub_it : it.second) {		// check associated blocks to it
			//	Update pointer to the reference of the associated blocks
			m_files[it.first].UpdateBlockSN(m_blocks[sub_it]);
		}
	}
}

bool GA_Migration::IsFirstChar(ifstream & in, char ch)
{
	char c;
	int cur_pos = in.tellg();
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
	GA_Population firstPop(10);	// firstPop holds 

}

