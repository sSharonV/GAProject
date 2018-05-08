#pragma once
#include <cstdlib>
#include <crtdbg.h>
#include "Ded_File.h"
#include "GA_Evolution.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;

enum class Selection { rou_whe_sel, lin_rank_sel, tour_sel };
enum class Crossover { one_point_cro, two_point_cro, uni_cro };
enum class Mutation { sin_point_mut, uni_point_mut };
enum class BytesMeasure {kilo, mega, giga};

class GA_Evolution;

struct general_prop{
	Selection g_sel_mode;
	Crossover g_cros_mode;
	Mutation g_mut_mode;
	int g_population_size;
	long double g_over_percent;
	int g_generations;
	int g_elit_best;
	int g_start_fix;
	long double g_epsilon;
	BytesMeasure g_eps_size;
	bool trueFor_KB;
	long double g_kb;
	BytesMeasure g_kb_size;
	long double g_percent;
	long double g_totalKB;
	long double g_KBforMig;
};

class GA_Migration {
	shared_ptr<map<string, shared_ptr<Ded_Block>>> m_blocks;
	shared_ptr<map<string, shared_ptr<Ded_File>>> m_files;
	shared_ptr<general_prop> mig_props;
	//GA_Migration* m_migInstance;
	pair<string,unsigned long> m_min_block_size;
	//static GA_Migration m_migInstance;
	
public:
	//static shared_ptr<GA_Migration> GetCurInstance(GA_Migration instance);
	static shared_ptr<GA_Migration> GetCurInstance();	// For any further use...
	
	//~GA_Migration();
	//GA_Migration(const GA_Migration &other);
	void InitBipartiteGraph(ifstream &input);
	void SetGeneralProperties(general_prop &properties);
	general_prop GetProperties();
	void SafeExit();
	void RunGeneticAlgo();
	long double GetSolutionLimitSize();
	long double GetSystemSize();
	unsigned long GetMinBlockSize();
	/*
		Return the referenece of original maps
		-	In order to reuse the memory of the allocated objects
	*/
	shared_ptr<map<string, shared_ptr<Ded_Block>>> GetBlocks();
	//const map<string, Ded_Block>& GetBlocks() const;
	shared_ptr<map<string, shared_ptr<Ded_File>>> GetFiles();

private:
	GA_Migration();	// Default constructor (does nothing..)
	void InitKBForMig();
	void InitBlockVector(ifstream &input);
	void InitFileVector(ifstream & input, shared_ptr<map<string, string>> blocks, shared_ptr<map<string, vector<string>>> f_b);
	void ConnectBlockAndFiles(shared_ptr<map<string, string>> block_sizes, shared_ptr<map<string, vector<string>>> f_b);
	string InputHelper(ifstream &in);
	bool IsFirstChar(ifstream &in, char ch);
	//static void DeleteCurInstance();
};



