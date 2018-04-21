#pragma once
#include "Ded_Block.h"

#include <vector>
#include <map>
#include "iostream"

using namespace std;

class Ded_Block;

class Ded_File {
	unsigned int f_sn;
	string f_id;
	unsigned int f_dir_sn;
	int f_num_blocks;
	map<string,Ded_Block*> f_blocks;
	
public:
	Ded_File(unsigned int sn = 0, string id = "", unsigned int dir_sn = 0, int num_blocks = 0);
	void UpdateBlockSN(Ded_Block &block);
};