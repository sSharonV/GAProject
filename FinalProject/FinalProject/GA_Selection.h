#pragma once
#ifndef EVOLUTION_H
#include "GA_Evolution.h"
#endif // EVOLUTION_H
#include <algorithm>

using namespace std;

//class GA_SelectionRW;
class GA_Evolution;
class GA_Migration;
class GA_Population;

enum class Selection;

/*

struct less_than_obf {
	inline bool operator() (const shared_ptr<GA_Chromosome>& o1, const shared_ptr<GA_Chromosome>& o2) {
		return (o1->ObjectiveFunc() < o2->ObjectiveFunc());
	}
};*/

class GA_Selection {
protected:
	Selection s_sel_mode;
	int s_elit;
	weak_ptr<GA_Population> s_popul;
	shared_ptr<GA_Population> s_matingPool;
public:
	GA_Selection(Selection sel, int elit);
	~GA_Selection();
	virtual void InitMatingPool(shared_ptr<GA_Population> population) = 0;
protected:
	void InitElitism();
};

class GA_SelectionRW : public GA_Selection {
	long double m_totalFit;
public:
	GA_SelectionRW(Selection sel, int elit);
	virtual void InitMatingPool(shared_ptr<GA_Population> population);
private:
	double CalcPercent(long double cardinal);
	
};