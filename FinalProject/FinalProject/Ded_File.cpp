#include "stdafx.h"
#include "Ded_File.h"


using namespace std;

Ded_File::Ded_File(unsigned int sn, string id, unsigned int dir_sn, unsigned long num_blocks)
	: f_sn(sn), f_id(id), f_dir_sn(dir_sn), f_num_blocks(num_blocks)
{
	using t_files = map<string, weak_ptr<Ded_Block>>;
	using il_files = initializer_list<t_files::value_type>;
	f_blocks = make_shared<t_files>(il_files{});
}

Ded_File::Ded_File(const Ded_File & other)
{
	this->f_blocks = (other.f_blocks);
	this->f_dir_sn = other.f_dir_sn;
	this->f_id = other.f_id;
	this->f_num_blocks = other.f_num_blocks;
	this->f_sn = other.f_sn;
}

Ded_File::~Ded_File()
{
	for (auto it : *f_blocks) {
		if (it.second.expired()) {
			it.second.reset();
		}
	}
}

string Ded_File::GetSN()
{
	return to_string(f_sn);
}

/*
	Returns the reference of the file's blocks (which is shared_ptr)
*/
shared_ptr<map<string, weak_ptr<Ded_Block>>> Ded_File::GetMyBlocks()
{
	return f_blocks;
}

void Ded_File::UpdateBlockSN(shared_ptr<Ded_Block> &block)
{
	(*f_blocks)[block->GetSN()] = block;
}

unsigned long Ded_File::GetNumBlocks()
{
	return f_num_blocks;
}
