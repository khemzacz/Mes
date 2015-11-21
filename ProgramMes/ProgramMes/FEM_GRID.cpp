#include "FEM_GRID.h"
#include "GlobalData.h"
#include "Node.h"


FEM_GRID::FEM_GRID(GlobalData* globaldata)
{
	this->globaldata = globaldata;
}


FEM_GRID::~FEM_GRID()
{
}



void FEM_GRID::generateFEM_GRID()
{
	elementy = new Element*[this->globaldata->getMe()];
	wezly = new Node*[this->globaldata->getMn()];
	/* tworze wezly i elementy */

	for (int i = 0; i < this->globaldata->getMn(); i++)
	{
		wezly[i] = new Node(i);
	}

	for (int i = 0; i < this->globaldata->getMe();i++) // od razu w konstruktorze podaje id wezlow
	{
		elementy[i] = new Element(i,i,(i+1)); // (id elementu, id pierwszego wezla dla elementu i, id drugiego wezla dla elementu i)
	}



}

void FEM_GRID::setBoundryConditions(double q, double alfa_d_t)
{
	wezly[0]->setQ(this->globaldata->getQ());
}