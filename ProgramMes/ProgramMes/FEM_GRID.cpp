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
		elementy[i].createK_lokalne();
		elementy[i].createF_lokalne();
	}
	for (int i = 0; i < globaldata->getMn(); i++)
	{
		wezly[i].setr(i*globaldata->getdeltaR());
		wezly[i].setTemp(gb->gett0());

	}

}






void FEM_GRID::calculateLocalMatriciesAndLocalVectors()
{
	for (int i = 0; i < gb->getMe(); i++)
	{
		elementy[i].calculateLocalMatricies(gb->getdeltaTau());

	}
}

void FEM_GRID::buildGlobalMatrixAndVector()
{
// \/ Alokacja pamieci i inicjalizacja zerami \/

	K_globalne = new double*[gb->getMn()];
	for (int i = 0; i < gb->getMn(); i++)
	{
		K_globalne[i] = new double[gb->getMn()+1];
	}
	for (int i = 0; i < gb->getMn(); i++)
		for (int j = 0; j < gb->getMn()+1; j++) // +1 dla póŸniejszego wpisania do ost. kol. wektora F (potrzebne do implementacji metody Gaussa)
		{
			K_globalne[i][j] = 0.0;
		}
	F_globalne = new double[gb->getMn()];
	for (int i = 0; i < gb->getMn(); i++)
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
		F_globalne[0 + i] += F_lokalne[0] * -1 ;
		F_globalne[1 + i] += F_lokalne[1] * -1;

	}


}

void FEM_GRID::printK_globalne()
{
	cout << endl<<endl;
	for (int i = 0; i < gb->getMn(); i++)
	{
	
		for (int j = 0; j < gb->getMn()+1; j++)
		{
			cout << K_globalne[i][j] << "\t";
		}
		cout << endl;
	}
}

void FEM_GRID::printF_globalne()
{
	cout << endl << endl;
	for (int i = 0; i < gb->getMn(); i++)
	{
		cout << F_globalne[i] << endl;
	}
}

void FEM_GRID::liczPoCzasie()
{
	double a = gb->getk() / (gb->getc()*gb->getp());
	double dTau = (gb->getdeltaR()*gb->getdeltaR() / (0.5*a));
	double TauMax = gb->getTauMax();
	cout << "TauMax: " << TauMax << endl;
	double nTime = (TauMax / dTau) +1;
	cout << "nTime: " << nTime << endl;
	dTau = gb->getdeltaTau();
	for (int iTime = 1; iTime <= nTime;iTime++)
	{
		calculateLocalMatriciesAndLocalVectors(); // przeliczanie lokalnych
		buildGlobalMatrixAndVector();
		solveSystemOfEquations();// rozw + pozmienianie temperatur w NOPach
		printTempratures();
		
		

	}
		
}

void FEM_GRID::solveSystemOfEquations()
{
#define Hg K_globalne
#define Pg F_globalne

	for (int i = 0; i < gb->getMn(); i++)
	{
		Hg[i][gb->getMn()] = -1*Pg[i];
	}

	for (int i = 0; i <gb->getMn() ;i++) // pivotisation
	{
		for (int k = i + 1; k < gb->getMn();k++)
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


	//printK_globalne(); // OK BZ

	
	for (int i = 0; i < gb->getMn() ; i++) // loop to perform gaussian elim.
	{
		for (int k = i+1; k < gb->getMn(); k++)
		{
			double t = (Hg[k][i] / Hg[i][i]);
			for (int j = 0; j <= gb->getMn(); j++)
			{
				Hg[k][j] = Hg[k][j] - (t*Hg[i][j]);
				//if (Hg[k + 1][j]<0.00000001 && Hg[k + 1][j]> -0.00000001)
				//	Hg[k + 1][j] = 0;
			}
		}
	}

//	printK_globalne();
	//gb->wypiszPg();

	//gb->tworzWektorT(gb->getMn());
	//double* w_r = gb->getWektorT();

	double* w_r = new double[gb->getMn()];
	for (int i = 0; i < gb->getMn()+1; i++)
		w_r[i] = 0.0;
	for (int i = (gb->getMn() - 1); i >= 0; i--) // back subs
	{
		w_r[i] = (Hg[i][gb->getMn()]);

		for (int j = 0; j <= gb->getMn() ; j++)
		
			if(j!=i)
				w_r[i] = (w_r[i] - Hg[i][j] * w_r[j]);
		w_r[i] = (w_r[i] / Hg[i][i]);
		//	w_r[i] -= Hg[i][j] * w_r[j];
		//		w_r[i] -= - Hg[i][j] * w_r[j];
		//
		//w_r[i] = (w_r[i] / Hg[i][i]);
		//cout << endl << w_r[i]<<endl;
	}
	//printK_globalne();
	//gb->wypiszPg();

	for (int i = 0; i < gb->getMn(); i++)
	{
		wezly[i].setTemp(w_r[i]);

	}

}

void FEM_GRID::printTempratures()
{
	cout << endl << endl;
	for (int i = 0; i < gb->getMn(); i++)
	{
		cout << wezly[i].getTemp() << "\t";
	}
}

void FEM_GRID::free()
{

}