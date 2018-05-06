#include "stdafx.h"
#include "Ded_Block.h"

Ded_Block::Ded_Block(unsigned int sn, string id, int n_s_f, int s)
	: b_sn(sn), b_id(id), num_shared_files(n_s_f), size(s)
{
	using t_block = map<string, Ded_File*>;
	using il_blocks = initializer_list<t_block::value_type>;
	b_files = make_shared<t_block>(il_blocks{});
}

Ded_Block::~Ded_Block()
{
	
}

void Ded_Block::setBlockSize(unsigned int s)
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
