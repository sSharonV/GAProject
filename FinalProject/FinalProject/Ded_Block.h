#pragma once
#include "Ded_File.h"
#include <vector>
#include <string>

using namespace std;

class Ded_File;

class Ded_Block {
	unsigned int b_sn;
	string b_id;
	int num_shared_files;
	unsigned int size;
	vector<Ded_File*> b_files;

public:
	Ded_Block(unsigned int sn = 0, string id = "", int n_s_f = 0, int s = 0);
	void setBlockSize(unsigned int s);
	void AddFile(Ded_File &f);
	string GetSN();
};