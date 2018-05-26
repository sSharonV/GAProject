#pragma once
#include "Ded_File.h"
#include <memory>
#include <map>
#include <string>

using namespace std;

class Ded_File;

/*
	Block is a touple of sn, id, size and a record of the files which are associated with it.
	-	The map of the files consists of weak_ptr, because the original referenece isn't stored in Block instance
*/
class Ded_Block {
	/*
		SN of blocks
	*/
	unsigned long b_sn;

	/*
		ID of blocks
	*/
	string b_id;

	/*
		Number of shared files
	*/
	int num_shared_files;

	/*
		Size in bytes of blocks
	*/
	unsigned long size;

	/*
		Smart pointer to map of associsated files
	*/
	shared_ptr<map<string, weak_ptr<Ded_File>>> b_files;

	/*
		Smart pointer to map of neighboor blocks
	*/
	shared_ptr<map<string, weak_ptr<Ded_Block>>> neighboors;

public:
	Ded_Block(unsigned long sn = 0, string id = "", int n_s_f = 0, unsigned long s = 0);
	Ded_Block(const Ded_Block& other);
	~Ded_Block();
	void setBlockSize(unsigned long s);
	string GetSN();
	unsigned long GetSize();

	/*
		Initialize a reference to a given file 'f'
	*/
	void AddFile(shared_ptr<Ded_File> &f);

	/*
		Returns pointer to a map of the neighboor blocks of Block instance
	*/
	shared_ptr<map<string, weak_ptr<Ded_Block>>> GetMyNeighboors();
};