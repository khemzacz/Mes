#pragma once
#include "Element.h"
#include "GlobalData.h"


class FEM_GRID
{
public:
	FEM_GRID(GlobalData* globaldata);
	~FEM_GRID();


	void setBoundryConditions();
	void generateFEM_GRID();
	void calculateLocalMatriciesAndLocalVectors();
	void buildGlobalMatrixAndVector(int wymiar);
private:
	Element** elementy;
	Node** wezly;
	GlobalData* globaldata;

};

