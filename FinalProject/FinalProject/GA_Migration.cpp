#include "stdafx.h"
#include "GA_Migration.h"


GA_Migration::GA_Migration(ifstream &input)
{
	map<string, string> blocks_size;
	map<string, vector<string>> files_blocks;
	InitFileVector(input, blocks_size, files_blocks);
	InitBlockVector(input);
	ConnectBlockAndFiles(blocks_size, files_blocks);
}


void GA_Migration::InitBlockVector(ifstream& input)
{
	string line;
	string block_sn, block_id, num_files;
	string file_sn;
	int n_files;
	int length;
	bool main_flag = true, flag = true;

	// guerantee pointing to start of input file
	input.clear();
	input.seekg(0, ios::beg);
	// start processing the blocks within the textf=file
	while (main_flag) {
		getline(input, line);
		if (line.find("B,") == string::npos)		 // save the position of the files
			length = input.tellg();
		else {
			while (IsFirstChar(input, 'B')) {	 // start processing the files
				if (flag) {
					input.seekg(length - 89);					// start at the beggining of the file sequence
					length = input.tellg();
					flag = false;
				}
				else {
					length = input.tellg();
					input.seekg(length + 3);
				}
				block_sn = InputHelper(input);
				block_id = InputHelper(input);
				num_files = InputHelper(input);
				n_files = stoi(num_files);
				m_blocks[block_sn] = Ded_Block(stoi(block_sn), block_id, n_files);
				for (int i = 0; i < n_files; i++) {
					file_sn = InputHelper(input);
					m_blocks[block_sn].AddFile(m_files[file_sn]);
				}
			}
		}
		if (!flag) main_flag = false;
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
	}
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
	// TODO ALOT
}



