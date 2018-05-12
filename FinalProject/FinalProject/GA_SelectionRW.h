
/*
#pragma once
#ifndef EVOLUTION_H
#include "GA_Evolution.h"
#endif // EVOLUTION_H
#ifndef MIGRATION_H
#include "GA_Migration.h"
#endif#endif // !SELECTIONRW_H
#ifndef SELECTION_H
#include "Selections.h"
#endif // SELECTION_H

//enum class Selection;
//class GA_Selection;

class GA_SelectionRW : public GA_Selection {
	long double m_totalFit;
public:
	GA_SelectionRW(Selection sel, int elit);
	virtual void InitMatingPool(shared_ptr<GA_Population> population);
private:
	double CalcPercent(long double cardinal);
};*/