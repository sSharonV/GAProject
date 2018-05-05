#pragma once

#include "GA_Migration.h"

class GA_Mutation {
	void (GA_Migration::*m_mutationMod)();
public:
	GA_Mutation(GA_Migration::Mutation mutation_mode) {
		switch (mutation_mode)
		{
		case GA_Migration::sin_point_mut:
			break;
		case GA_Migration::uni_point_mut:
			break;
		default:
			break;
		}
	}
};