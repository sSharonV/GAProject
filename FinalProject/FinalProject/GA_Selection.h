#pragma once
#include "GA_Migration.h"

class GA_Selection {
protected:
	GA_Selection() {}
	virtual void Selection(GA_Population population) = 0;
};