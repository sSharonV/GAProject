#pragma once
#include "Ded_File.h"
#include <memory>
#include <map>
#include <string>

using namespace std;

class Ded_File;

class Ded_Block {
	unsigned long b_sn;
	string b_id;
	int num_shared_files;
	unsigned long size;
	shared_ptr<map<string, Ded_File*>> b_files;

public:
	Ded_Block(unsigned long sn = 0, string id = "", int n_s_f = 0, unsigned long s = 0);
	~Ded_Block();
	void setBlockSize(unsigned long s);
	void AddFile(Ded_File &f);
	string GetSN();
	unsigned long GetSize();
	map<string, Ded_Block*> GetMyNeighboors();
};