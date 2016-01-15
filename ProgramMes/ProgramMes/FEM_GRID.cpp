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



void FEM_GRID::generateFEM_GRID()
{

}

void FEM_GRID::setBoundryConditions()
{

}

void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	
}

void FEM_GRID::buildGlobalMatrixAndVector(int wymiar)
{

}

void FEM_GRID::free()
{

}