#pragma once
#include "Element.h"
#include "GlobalData.h"


class FEM_GRID
{
public:
	FEM_GRID(GlobalData* globaldata);
	~FEM_GRID();



	void createElementsAndNodes();
	void calculateLocalMatriciesAndLocalVectors();
	void buildGlobalMatrixAndVector();
	void printK_globalne();
	void printF_globalne();
	void liczPoCzasie();
	void solveSystemOfEquations();
	void printTempratures();
	void free();
private:
	Element* elementy;
	Node* wezly;
	double** K_globalne;
	double* F_globalne;

	GlobalData* globaldata;

};

