#pragma once

#include "GA_Migration.h"

class GA_Crossover {
	void (GA_Crossover::*m_crossoverMod)();
public:
	GA_Crossover(int crossover_mode) {
	}
};