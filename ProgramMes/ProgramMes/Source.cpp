#pragma once
#include <iostream>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <string>
#include "GlobalData.h"
#include "FEM_GRID.h"

using namespace std;


int main()
{
	GlobalData* globaldata = new GlobalData();
	FEM_GRID* fem_grid = new FEM_GRID(globaldata);

	globaldata->pobierz_dane();
	globaldata->wypisz_dane();

	fem_grid->generateFEM_GRID();
	fem_grid->setBoundryConditions();
	fem_grid->calculateLocalMatriciesAndLocalVectors();
	fem_grid->buildGlobalMatrixAndVector(globaldata->getMn());
	globaldata->wypiszWektorT();
	

	

	fem_grid->free();
	globaldata->free();
	delete globaldata;
	delete fem_grid;
	system("PAUSE");
	return 0;
}