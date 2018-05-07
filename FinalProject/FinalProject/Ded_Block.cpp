#include "stdafx.h"
#include "Ded_Block.h"

Ded_Block::Ded_Block(unsigned long sn, string id, int n_s_f, unsigned long s)
	: b_sn(sn), b_id(id), num_shared_files(n_s_f), size(s)
{
	using t_block = map<string, Ded_File*>;
	using il_blocks = initializer_list<t_block::value_type>;
	b_files = make_shared<t_block>(il_blocks{});
}

Ded_Block::~Ded_Block()
{
	
}

void Ded_Block::setBlockSize(unsigned long s)
{
	size = s;
}

void Ded_Block::AddFile(Ded_File &f)
{
	(*b_files)[f.GetSN()] = &f;
}

string Ded_Block::GetSN()
{
	return to_string(b_sn);
}

unsigned long Ded_Block::GetSize()
{
	return size;
}

/*
	Returns vector of pointers to the original blocks whom connected to this block
*/
map<string, Ded_Block*> Ded_Block::GetMyNeighboors()
{
	map<string, Ded_Block*> neighboors;
	for (auto it_file : *(b_files)) {	// for every file assicated with this block
		for (auto it_n_block : it_file.second->GetMyBlocks()) {	// check the blocks which are this neighboors
			neighboors[it_n_block.second->GetSN()] = it_n_block.second;
		}
	}
	return neighboors;
}

