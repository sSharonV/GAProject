#pragma once
#include "Ded_File.h"
#include "GA_Chromosome.h"
#include "GA_Population.h"
#include "GA_Selection.h"
#include "GA_Crossover.h"
#include "GA_Mutation.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class GA_Migration {
	map<string, Ded_Block> m_blocks;
	map<string, Ded_File> m_files;
	unsigned long m_sizeLimit;
	static GA_Migration* m_migInstance;
public:
	enum Selection { rou_whe_sel, lin_rank_sel, tour_sel };
	enum Crossover { one_point_cro, two_point_cro, uni_cro };
	enum Mutation { sin_point_mut, uni_point_mut };
	GA_Migration(ifstream &input);
	unsigned long SolutionSize();
	static GA_Migration* GetInstance(ifstream &input);
	static GA_Migration* GetInstance();
private:
	void InitBlockVector(ifstream &input);
	void GA_Migration::InitFileVector(ifstream & input, map<string, string> &blocks, map<string, vector<string>> &f_b);
	void ConnectBlockAndFiles(map<string, string> &block_sizes, map<string, vector<string>> &f_b);
	void RunGeneticAlgo();
	string InputHelper(ifstream &in);
	bool IsFirstChar(ifstream &in, char ch);
};