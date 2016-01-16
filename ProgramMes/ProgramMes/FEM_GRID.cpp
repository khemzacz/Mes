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
		elementy[i].setID(i + 1);
	}
	for (int i = 0; i < globaldata->getMn(); i++)
	{
		wezly[i].setr(i*globaldata->getdeltaR());

	}

}






void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	for (int i = 0; i < gb->getMe(); i++)
	{
		elementy[i].createK_lokalne();
		elementy[i].createF_lokalne();
		elementy[i].calculateLocalMatricies();

	}
}

void FEM_GRID::buildGlobalMatrixAndVector()
{
// \/ Alokacja pamieci i inicjalizacja zerami \/

	K_globalne = new double*[gb->getMn()];
	for (int i = 0; i < gb->getMn(); i++)
	{
		K_globalne[i] = new double[gb->getMn()];
	}
	for (int i = 0; i < gb->getMn(); i++)
		for (int j = 0; j < gb->getMn(); j++)
		{
			K_globalne[i][j] = 0.0;
		}
	F_globalne = new double[gb->getMn()];
	for (int i = 0; i < gb->getMn; i++)
	{
		F_globalne[i] = 0.0;
	}


// \/ Wype?nianie warto?ciami \/

	double **K_lokalne;
	double *F_lokalne;
	for (int i = 0; i < gb->getMe(); i++)
	{
		K_lokalne = elementy[i].getK_lokalne();
		K_globalne[0 + i][0 + i] += K_lokalne[0][0];
		K_globalne[1 + i][0 + i] += K_lokalne[1][0];
		K_globalne[0 + i][1 + i] += K_lokalne[0][1];
		K_globalne[1 + i][1 + i] += K_lokalne[1][1];

		F_lokalne = elementy[i].getF_lokalne();
		F_globalne[0 + i] += F_lokalne[0] ;
		F_globalne[1 + i] += F_lokalne[1] ;

	}


}

void FEM_GRID::printK_globalne()
{
	for (int i = 0; )
}

void FEM_GRID::free()
{

}