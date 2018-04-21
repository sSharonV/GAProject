#include "stdafx.h"
#include "Ded_File.h"


using namespace std;

Ded_File::Ded_File(unsigned int sn, string id, unsigned int dir_sn, int num_blocks)
	: f_sn(sn), f_id(id), f_dir_sn(dir_sn), f_num_blocks(num_blocks)
{
	//f_blocks.reserve(num_blocks);
}

void Ded_File::AddBlankBlock(string block)
{
	f_blocks[block] = NULL;
}

void Ded_File::UpdateBlockSN(Ded_Block& block)
{
	f_blocks[block.GetSN()] = &block;
}
