#include "stdafx.h"
#include "Ded_Block.h"

Ded_Block::Ded_Block(unsigned long sn, string id, int n_s_f, unsigned long s)
	: b_sn(sn), b_id(id), num_shared_files(n_s_f), size(s)
{
	using t_block = map<string, weak_ptr<Ded_File>>;
	using il_blocks = initializer_list<t_block::value_type>;
	using t_neigh = map<string, weak_ptr<Ded_Block>>;
	using il_neigh = initializer_list<t_neigh::value_type>;
	neighboors = make_shared<t_neigh>(il_neigh{});
	b_files = make_shared<t_block>(il_blocks{});
	//neighboors = make_shared<t_neigh>(il_neigh{});
}

Ded_Block::Ded_Block(const Ded_Block & other)
{
	(this->b_files) = (other.b_files);
	this->neighboors = other.neighboors;
	this->b_id = other.b_id;
	this->b_sn = other.b_sn;
	this->num_shared_files = other.num_shared_files;
	this->size = other.size;
}

Ded_Block::~Ded_Block()
{
	for (auto it : *b_files) {
		if (it.second.expired()) {
			it.second.reset();
		}
	}
}

void Ded_Block::setBlockSize(unsigned long s)
{
	size = s;
}

void Ded_Block::AddFile(shared_ptr<Ded_File> &f)
{
	(*b_files)[f->GetSN()] = f;
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

shared_ptr<map<string, weak_ptr<Ded_Block>>> Ded_Block::GetMyNeighboors()
{
	//map<string, weak_ptr<Ded_File>>::iterator it_file;
	
	for (auto it_file : *b_files) 							// For each file
		if (auto sh_file = it_file.second.lock()) {			// Retrive strong reference
			if (sh_file->GetNumBlocks() > 1) {
				for (auto it_block : *(sh_file->GetMyBlocks())) 	// for each associated block
					if (auto sh_block = it_block.second.lock()) {
						string sn = sh_block->GetSN();
						if (neighboors->find(sn) == neighboors->end()
							&& (sn.compare(this->GetSN()) != 0)) // the block isn't recognized as neightboor yet
						{
							(*neighboors)[sh_block->GetSN()] = sh_block;
						}
					}
			}
		}
	return neighboors;
}

