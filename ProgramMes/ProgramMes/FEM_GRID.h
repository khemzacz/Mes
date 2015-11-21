#pragma once
#include "Element.h"
#include "GlobalData.h"


class FEM_GRID
{
public:
	FEM_GRID(GlobalData* globaldata);
	~FEM_GRID();


	void setBoundryConditions(double q, double alfa_d_t);
	void generateFEM_GRID();

private:
	Element** elementy;
	Node** wezly;
	GlobalData* globaldata;

};

