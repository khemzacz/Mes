#include "FEM_GRID.h"
#include "GlobalData.h"
#include "Node.h"

#define gb globaldata

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
		elementy[i] = new Element(i,i,(i+1),gb->getL(),gb->getMe()); // (id elementu, id pierwszego wezla dla elementu i, id drugiego wezla dla elementu i)
	}



}

void FEM_GRID::setBoundryConditions(double q, double alfa_d_t)
{
	wezly[0]->setQ(this->globaldata->getQ());
	//wezly[3]->setAlfaDT(this->globaldata->getAlfaDT());
}

void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	double Sk = gb->getS()*gb->getK();
	for (int i = 0; i < globaldata->getMe()-1; i++)
	{
		elementy[i]->setH_lokalne(Sk/elementy[i]->getDl(),0,0);
		elementy[i]->setH_lokalne(- 1 * Sk / elementy[i]->getDl(), 1, 0);
		elementy[i]->setH_lokalne(- 1 * Sk / elementy[i]->getDl(), 0, 1);
		elementy[i]->setH_lokalne(Sk / elementy[i]->getDl(), 1, 1);
	}

	elementy[1]->setH_lokalne(Sk / elementy[1]->getDl(), 0, 0);
	elementy[1]->setH_lokalne(-1 * Sk / elementy[1]->getDl(), 1, 0);
	elementy[1]->setH_lokalne(-1 * Sk / elementy[1]->getDl(), 0, 1);
	elementy[1]->setH_lokalne(Sk / elementy[1]->getDl()+gb->getAlfa()*gb->getS(), 1, 1);



	/* To-Do To samo dla P */
}