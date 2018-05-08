#pragma once
#include "Ded_Block.h"
#include <memory>
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
	shared_ptr<map<string, weak_ptr<Ded_Block>>> f_blocks;
	
public:
	Ded_File(unsigned int sn = 0, string id = "", unsigned int dir_sn = 0, int num_blocks = 0);
	Ded_File(const Ded_File& other);
	~Ded_File();
	string GetSN();
	map<string, weak_ptr<Ded_Block>> GetMyBlocks();
	void UpdateBlockSN(shared_ptr<Ded_Block> &block);
};