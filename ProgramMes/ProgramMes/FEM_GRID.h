#pragma once
#include "Element.h"
class FEM_GRID
{
public:
	FEM_GRID();
	~FEM_GRID();



	void generateFEM_GRID();

private:
	Element** elementy;
	Node** wezly;

};

