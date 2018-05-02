#pragma once
#include "Ded_File.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <geneial\core\operations\crossover\BaseCrossoverOperation.h>

using namespace std;
using namespace boost;

class GA_Migration {
	map<string, Ded_Block> m_blocks;
	map<string, Ded_File> m_files;
	unsigned long m_sizeLimit;


public:
	GA_Migration(ifstream &input);
private:
	void InitBlockVector(ifstream &input);
	void GA_Migration::InitFileVector(ifstream & input, map<string, string> &blocks, map<string, vector<string>> &f_b);
	void ConnectBlockAndFiles(map<string, string> &block_sizes, map<string, vector<string>> &f_b);
	void RunGeneticAlgo();
	string InputHelper(ifstream &in);
	bool IsFirstChar(ifstream &in, char ch);
};