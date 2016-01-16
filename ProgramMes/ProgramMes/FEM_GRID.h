#pragma once
#include "Element.h"
#include "GlobalData.h"


class FEM_GRID
{
public:
	FEM_GRID(GlobalData* globaldata);
	~FEM_GRID();



	void createElementsAndNodes();


	void setBoundryConditions();
	void generateFEM_GRID();
	void calculateLocalMatriciesAndLocalVectors();
	void buildGlobalMatrixAndVector(int wymiar);
	void free();
private:
	Element* elementy;
	Node* wezly;
	GlobalData* globaldata;

};

