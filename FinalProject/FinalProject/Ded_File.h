#pragma once
#include "Ded_Block.h"
#include <memory>
#include <vector>
#include <map>
#include "iostream"

using namespace std;

class Ded_Block;

/*
	Files is a touple of sn, id, dir_sn and a record of the blocks which are associated with it.
	-	The map of the blocks consists of weak_ptr, because the original reference isn't stored in File instance
*/
class Ded_File {
	/*	
		Sn of files
	*/
	unsigned int f_sn;

	/*
		ID of files
	*/
	string f_id;

	/*
		dir_sn of files
	*/
	unsigned int f_dir_sn;

	/*
		Number of shared blocks
	*/
	unsigned long f_num_blocks;

	/*
		Smart pointer to map of assocated blocks
	*/
	shared_ptr<map<string, weak_ptr<Ded_Block>>> f_blocks;
	
public:
	Ded_File(unsigned int sn = 0, string id = "", unsigned int dir_sn = 0, unsigned long num_blocks = 0);
	Ded_File(const Ded_File& other);
	~Ded_File();
	string GetSN();
	shared_ptr<map<string, weak_ptr<Ded_Block>>> GetMyBlocks();
	void UpdateBlockSN(shared_ptr<Ded_Block> &block);
	unsigned long GetNumBlocks();
};