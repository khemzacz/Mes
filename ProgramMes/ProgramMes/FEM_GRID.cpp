#include <iostream>
#include "FEM_GRID.h"
#include "GlobalData.h"
#include "Node.h"

#define gb globaldata

using namespace std;

FEM_GRID::FEM_GRID(GlobalData* globaldata)
{
	this->globaldata = globaldata;
}


FEM_GRID::~FEM_GRID()
{
}

void FEM_GRID::createElementsAndNodes()
{
	this->elementy = new Element[globaldata->getMe()];
	this->wezly = new Node[globaldata->getMn()];
	for (int i = 0; i < globaldata->getMe();i++)
	{
		elementy[i].setGlobalData(globaldata); // elymenty dostaja dostep do globalnych danych np. k, deltaR
		elementy[i].setNOP1(&wezly[i]);
		elementy[i].setNOP2(&wezly[i + 1]);
	}
	for (int i = 0; i < globaldata->getMn(); i++)
	{
		wezly[i].setr(i*globaldata->getdeltaR());

	}

}



void FEM_GRID::generateFEM_GRID() //
{

}

void FEM_GRID::setBoundryConditions()
{

}

void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	for (int i = 0; i < gb->getMe(); i++)
	{
		elementy[i].createK_lokalne();
		elementy[i].calculateK_lokalne();

	}
}

void FEM_GRID::buildGlobalMatrixAndVector(int wymiar)
{

}

void FEM_GRID::free()
{

}