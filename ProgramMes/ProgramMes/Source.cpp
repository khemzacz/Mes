#pragma once
#include <iostream>
#include <cstdio>
#include <conio.h>
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


	if (!globaldata->pobierz_dane())
	{
		cout << endl << "Brak pliku GlobalData.txt";
		_getch();
		return 0;
	}
	globaldata->wypisz_dane();

	
	fem_grid->createElementsAndNodes();
	fem_grid->liczPoCzasie();
	//fem_grid->calculateLocalMatriciesAndLocalVectors();
	//fem_grid->buildGlobalMatrixAndVector();
	//fem_grid->printK_globalne();
	//fem_grid->printF_globalne();
	//fem_grid->solveSystemOfEquations();
	//fem_grid->printTempratures();
	//fem_grid->liczPoCzasie();

	//

	fem_grid->free();
	delete globaldata;
	delete fem_grid;
	system("PAUSE");
	return 0;
}