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
	elementy = new Element*[gb->getMe()];
	wezly = new Node*[gb->getMn()];
	/* tworze wezly i elementy */

	for (int i = 0; i < gb->getMn(); i++)
	{
		wezly[i] = new Node(i);
	}

	for (int i = 0; i < gb->getMe();i++) // od razu w konstruktorze podaje id wezlow
	{
		elementy[i] = new Element(i,i,(i+1),gb->getL(),gb->getMe()); // (id elementu, id pierwszego wezla dla elementu i, id drugiego wezla dla elementu i)
	}



}

void FEM_GRID::setBoundryConditions()
{
	wezly[0]->setQ(this->gb->getQ()*this->gb->getS());
	wezly[gb->getMn()-1]->setAlfaDT(this->gb->getS()*this->gb->getAlfa()*this->gb->getT());
}

void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	double Sk = (gb->getS()*gb->getK());
	double** H_lokalne;
	int i = 0;
	for (; i < gb->getMe()-1; i++)
	{
		H_lokalne = elementy[i]->getH_lokalne();
		H_lokalne[0][0] = Sk/elementy[i]->getDl() ;
		H_lokalne[1][0] = - 1 *( Sk / elementy[i]->getDl());
		H_lokalne[0][1] =- 1 * (Sk / elementy[i]->getDl());
		H_lokalne[1][1] = Sk / elementy[i]->getDl();
	}
	H_lokalne = elementy[i]->getH_lokalne();
	H_lokalne[0][0] = Sk / elementy[i]->getDl();
	H_lokalne[1][0] =  -1 * (Sk / elementy[i]->getDl());
	H_lokalne[0][1] = -1 * (Sk / elementy[i]->getDl());
	H_lokalne[1][1] = ((Sk / elementy[i]->getDl())+(gb->getAlfa()*gb->getS()));

	double* P_lokalne;
	P_lokalne = elementy[0]->getP_lokalne();
	(P_lokalne[0] = 1 * gb->getQ()*gb->getS());
	(P_lokalne[1] = 0);
	i = 1;
	for (; i < gb->getMe() - 1; i++)
	{
		P_lokalne = elementy[i]->getP_lokalne();
		(P_lokalne[0] = 0);
		(P_lokalne[1] = 0);

	}

	P_lokalne = elementy[i]->getP_lokalne();
	(P_lokalne[0] = 0);
	(P_lokalne[1] = -1 * gb->getAlfa()*gb->getT()*gb->getS());
	
}

void FEM_GRID::buildGlobalMatrixAndVector(int wymiar)
{
	gb->tworzGlobalnaMacierzH(wymiar);
	gb->tworzGlobalnyWektorP(wymiar);
	double **H_globalne = gb->getH_globalne();
	// cout << endl << H_globalne << endl; // adres OK
	double *P_globalne = gb->getP_globalne();
	
	double **H_lokalne;
	double *P_lokalne;


	for (int i = 0; i < gb->getMe(); i++)
	{
		H_lokalne = elementy[i]->getH_lokalne();
		H_globalne[0+i][0+i] += H_lokalne[0][0];
		H_globalne[1+i][0+i] += H_lokalne[1][0];
		H_globalne[0+i][1+i] += H_lokalne[0][1];
		H_globalne[1+i][1+i] += H_lokalne[1][1];

		P_lokalne = elementy[i]->getP_lokalne();
		P_globalne[0+i] += P_lokalne[0] * -1;
		P_globalne[1+i] += P_lokalne[1] * -1;
		
	}
#define Hg H_globalne
#define Pg P_globalne

	for (int i = 0; i < gb->getMn(); i++)
	{
		Hg[i][gb->getMn() ] = Pg[i];
	}

//	gb->wypiszHg();
//	gb->wypiszPg();



	for (int i = 0; i < gb->getMn(); i++)
	{
		for (int k= i + 1; k < gb->getMn(); k++)
		{
			if (Hg[i][i] < Hg[k][i])
			{
				for (int j = 0; j <= gb->getMn(); j++)
				{
					double temp = Hg[i][j];
					Hg[i][j] = Hg[k][j];
					Hg[k][j] = temp;
				}
			}
		}
	}
	//gb->wypiszHg();

	for (int i = 0; i < gb->getMn() - 1; i++)
	{
		for (int k = i + 1; k < gb->getMn(); k++)
		{
			double t = Hg[k][i] / Hg[i][i];
			for (int j = 0; j <= gb->getMn(); j++)
			{
				Hg[k][j] = Hg[k][j] - t*Hg[i][j];
			}
		}
	}


//	gb->wypiszHg();
//	gb->wypiszPg();

	gb->tworzWektorT(gb->getMn());
	double* w_r = gb->getWektorT();

	for (int i = gb->getMn() - 1; i >= 0; i--)
	{
		w_r[i] = Hg[i][gb->getMn()];

		for (int j = 0; j <= gb->getMn(); j++)
			if (j != i)
				w_r[i] = w_r[i] - Hg[i][j] * w_r[j];
		w_r[i] = w_r[i] / Hg[i][i];
	}
	
	/*for (int i = 0; i < gb->getMn(); i++)
	{
		cout << "t" << i << " " << w_r[i] << endl;
	}*/


	/*for (int i =0; i < gb->getMn(); i++)
	{
		cout << "t" << i<< ": " << (wektor_rozwiazania[i] = Pg[i]) << endl;
	}*/

	/*

	//cout << endl << H_globalne[0][0] <<endl;
	H_lokalne = elementy[0]->getH_lokalne();
	H_globalne[0][0] = H_lokalne[0][0];
	//cout << endl << H_globalne[0][0] << endl;
	H_globalne[1][0] = H_lokalne[1][0];
	//cout << endl << H_globalne[1][0] << endl;
	H_globalne[0][1] = H_lokalne[0][1];
	H_globalne[1][1] = H_lokalne[1][1];

	H_lokalne = elementy[1]->getH_lokalne();
	H_globalne[1][1] += H_lokalne[0][0];
	H_globalne[2][1] = H_lokalne[1][0];
	H_globalne[1][2] = H_lokalne[0][1];
	H_globalne[2][2] = H_lokalne[1][1];
	// cout << endl << H_globalne[2][2] << endl; 

	P_lokalne = elementy[0]->getP_lokalne();
	P_globalne[0] += P_lokalne[0] * -1;
	P_globalne[1] += P_lokalne[1] * -1;
	P_lokalne = elementy[1]->getP_lokalne();
	P_globalne[1] += P_lokalne[0]*-1;
	P_globalne[2] += P_lokalne[1]*-1;

	*/
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << H_globalne[i][j] << " ";
		}
		cout << endl;
	} */
	/*
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
		- Hg[1][2] * Pg[2] * Hg[0][0] - Hg[2][2] * Pg[0] * Hg[1][0];
	double Wt3 = Hg[0][0] * Hg[1][1] * Pg[2] + Hg[1][0] * Hg[2][1] * Pg[0]
		+ Hg[2][0] * Hg[0][1] * Pg[2] - Hg[2][0] * Hg[1][1] * Pg[0]
		- Pg[1] * Hg[2][1] * Hg[0][0] - Pg[2] * Hg[0][1] * Hg[1][0];
	
	cout << "t1: " << Wt1 / W << endl;
	cout << "t2: " << Wt2 / W << endl;
	cout << "t3: " << Wt3 / W << endl;

	*/
}

void FEM_GRID::free()
{
	for (int j = 0; j < gb->getMe(); j++)
	{
		elementy[j]->free();
		delete elementy[j];
	}

	for (int i = 0; i < gb->getMn(); i++)
	{
		delete wezly[i];
	}

	delete elementy;
	delete wezly;
}