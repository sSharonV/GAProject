#pragma once
#include "Ded_File.h"
#include "GA_Evolution.h"
#include <cstdlib>
#include <crtdbg.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <memory> // !MIGRATION_H

using namespace std;

enum class Selection { rou_whe_sel, lin_rank_sel, tour_sel };
enum class Crossover { one_point_cro, two_point_cro, uni_cro };
enum class Mutation { sin_point_mut, uni_point_mut };
enum class BytesMeasure {kilo, mega, giga};

class GA_Evolution;

/*
	Struct for handling all the information which is used by the algorithm
*/
struct general_prop{
	Selection g_sel_mode;
	long double g_exp_val;
	Crossover g_cros_mode;
	Mutation g_mut_mode;
	int g_mut_rate;
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
	long double g_KB_minimal;
	unsigned long g_timeOut;
	long double g_initTime;
	long double g_execTime;
};

/*
	GA_Migration takes care of initializing a bipratite-graph which consists of instances of blocks whom are connected to their files - and vica verse
	-	The properties of migration operation can be acceseed via this class
	-	The instances of blocks and files are stored here
*/
class GA_Migration {
	shared_ptr<map<string, shared_ptr<Ded_Block>>> m_blocks;
	shared_ptr<map<string, shared_ptr<Ded_File>>> m_files;
	shared_ptr<general_prop> mig_props;
	pair<string,unsigned long> m_min_block_size;
	string m_fileName;
public:
	static shared_ptr<GA_Migration> GetCurInstance();	// For any further use...
	void SetFileName(string s);
	string GetFileName();
	string GetNumberOfFiles();
	string GetNumberOfBlocks();
	long double GetSolutionLimitSize();
	long double GetSystemSize();
	unsigned long GetMinBlockSize();
	string SelectionString();
	string CrossoverString();
	string MutationString();
	string EpsByteString();
	string SizeByteString();

	/*
		Initializing the maps which will help represent the bipratite-graph in the code
	*/
	void InitBipartiteGraph(ifstream &input);

	/*
		Returns the properties for migration
	*/
	shared_ptr<general_prop> GetProperties();
	
	/*
		Resets the maps and properties 
	*/
	void SafeExit();

	/*
		Initializing the size for migration in bytes - according to the user requirements
	*/
	void InitKBForMig();

	/*
		Start the genetic-algorithm which consists of Evolution process
	*/
	void RunGeneticAlgo();
	
	/*
		Return the referenece of original maps
		-	In order to reuse the memory of the allocated objects
	*/
	shared_ptr<map<string, shared_ptr<Ded_Block>>> GetBlocks();
	shared_ptr<map<string, shared_ptr<Ded_File>>> GetFiles();

private:
	GA_Migration();	// Default constructor (does nothing..)

	/*
		Parsing the input file for initializing the map of blocks
	*/
	void InitBlockVector(ifstream &input);

	/*
		Parsing the input file for initializing the map of files
	*/
	void InitFileVector(ifstream & input, shared_ptr<map<string, string>> blocks, shared_ptr<map<string, vector<string>>> f_b);

	/*
		Connecting the files to the blocks - and vice versa
	*/
	void ConnectBlockAndFiles(shared_ptr<map<string, string>> block_sizes, shared_ptr<map<string, vector<string>>> f_b);

	vector<string> InputHelper(ifstream &in, string to_search, unsigned long& num);
};



