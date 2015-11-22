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

void FEM_GRID::setBoundryConditions()
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


	elementy[0]->setP_lokalne(1 * gb->getQ()*gb->getS(), 0);
	elementy[0]->setP_lokalne(0 , 1);

	elementy[1]->setP_lokalne(0, 0);
	elementy[1]->setP_lokalne(-1 *gb->getAlfa()*gb->getT()*gb->getS(), 1);



	
}

void FEM_GRID::buildGlobalMatrixAndVector(int wymiar)
{
	gb->tworzGlobalnaMacierzH(wymiar);
	gb->tworzGlobalnyWektorP(wymiar);
	double **H_globalne = gb->getH_globalne();
	double *P_globalne = gb->getP_globalne();
	
	double **H_lokalne;
	double *P_lokalne;

	H_lokalne = elementy[0]->getH_lokalne();
	*H_globalne[0, 0] += *H_lokalne[0, 0];
	*H_globalne[1,0] += *H_lokalne[1, 0];
	*H_globalne[0, 1] += *H_lokalne[0, 1];
	*H_globalne[1, 1] += *H_lokalne[1, 1];

	H_lokalne = elementy[1]->getH_lokalne();
	*H_globalne[1, 1] += *H_lokalne[0, 0];
	*H_globalne[2, 1] += *H_lokalne[1, 0];
	*H_globalne[1, 2] += *H_lokalne[0, 1];
	*H_globalne[2, 2] += *H_lokalne[1, 1];

	P_lokalne = elementy[0]->getP_lokalne();
	P_globalne[0] += P_lokalne[0];
	P_globalne[1] += P_lokalne[1];
	P_lokalne = elementy[1]->getP_lokalne();
	P_globalne[1] += P_lokalne[0];
	P_globalne[2] += P_lokalne[1];
#define Hg H_globalne
#define Pg P_globalne
	double W = Hg[0][0] * Hg[1][1] * Hg[2][2] + Hg[1][0] * Hg[2][1] * Hg[0][2]
		+ Hg[2][0] * Hg[0][1] * Hg[1][2] - Hg[2][0] * Hg[1][1] * Hg[0][2]
		- Hg[1][2] * Hg[2][1] * Hg[0][0] - Hg[2][2] * Hg[0][1] * Hg[1][0];
	double Wt1 = Pg[0] * Hg[1][1] * Hg[2][2] + Pg[1] * Hg[2][1] * Hg[0][2]
		+ Pg[2] * Hg[0][1] * Hg[1][2] - Pg[2] * Hg[1][1] * Hg[0][2]
		- Hg[1][2] * Hg[2][1] * Pg[0] - Hg[2][2] * Hg[0][1] * Pg[1];
	double Wt2 = Hg[0][0] * Pg[1] * Hg[2][2] + Hg[1][0] * Pg[2] * Hg[0][2]
		+ Hg[2][0] * Pg[0] * Hg[1][2] - Hg[2][0] * Pg[1] * Hg[0][2]
		- Hg[1][2] * Pg[1] * Hg[0][0] - Hg[2][2] * Pg[1] * Hg[1][0];
	double Wt3 = Hg[0][0] * Hg[1][1] * Pg[2] + Hg[1][0] * Hg[2][1] * Pg[0]
		+ Hg[2][0] * Hg[0][1] * Pg[2] - Hg[2][0] * Hg[1][1] * Pg[0]
		- Pg[1] * Hg[2][1] * Hg[0][0] - Pg[2] * Hg[0][1] * Hg[1][0];
	// cout << "W: " << W << endl; // W wyszlo 0
	cout << "t1: " << Wt1 / W << endl;
	cout << "t2: " << Wt2 / W << endl;
	cout << "t3: " << Wt3 / W << endl;
}