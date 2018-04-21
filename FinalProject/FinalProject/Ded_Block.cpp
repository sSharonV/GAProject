#include "stdafx.h"
#include "Ded_Block.h"

Ded_Block::Ded_Block(unsigned int sn, string id, int n_s_f, int s)
	: b_sn(sn), b_id(id), num_shared_files(n_s_f), size(s)
{
	b_files.reserve(num_shared_files);
}

void Ded_Block::setBlockSize(unsigned int s)
{
	size = s;
}

void Ded_Block::AddFile(Ded_File &f)
{
	b_files.push_back(&f);
}

string Ded_Block::GetSN()
{
	return to_string(b_sn);
}
