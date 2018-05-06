#include "stdafx.h"
#include "Ded_File.h"


using namespace std;

Ded_File::Ded_File(unsigned int sn, string id, unsigned int dir_sn, int num_blocks)
	: f_sn(sn), f_id(id), f_dir_sn(dir_sn), f_num_blocks(num_blocks)
{
	using t_files = map<string, Ded_Block*>;
	using il_files = initializer_list<t_files::value_type>;
	f_blocks = make_shared<t_files>(il_files{});
}

Ded_File::~Ded_File()
{
	
}

string Ded_File::GetSN()
{
	return to_string(f_sn);
}

void Ded_File::UpdateBlockSN(Ded_Block& block)
{
	(*f_blocks)[block.GetSN()] = &block;
}
