#include <iostream>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <string>
#include "GlobalData.h"

using namespace std;

GlobalData::GlobalData()
{
}


GlobalData::~GlobalData()
{
}

void GlobalData::pobierz_dane()
{
	fstream plik;
	plik.open("GlobalData.txt", ios::in);
	if (plik.good() == true)
	{
		string test;
		double wartosc;
		while (1)
		{
			plik >> test >> wartosc;
			if (test == "KONIEC")
				break;
			else if (test == "Me:")
			{
				setMe((int)wartosc);
			}
			else if (test == "Mn:")
			{
				setMn((int)wartosc);
			}
			else if (test == "L:")
			{
				setL(wartosc);
			}
			else if (test == "S:")
			{
				setS(wartosc);
			}
			else if (test == "K:")
			{
				setK(wartosc);
			}
			else if (test == "Q:")
			{
				setQ(wartosc);
			}
			else if (test == "Alfa:")
			{
				setAlfa(wartosc);
			}
			else if (test == "T:")
			{
				setT(wartosc);
			}
			//cout << test << "\t" << wartosc << endl;
		}
		plik.close();
	}
	else
	{
		cout << "Brak pliku GlobalData.txt";
	}
	return;
}

void GlobalData::wypisz_dane()
{
	cout <<endl<< "Liczba Elementow (Me): " << getMe()<<endl;
	cout << "Liczba Wezlow (Mn): " << getMn() << endl;
	cout << "DLugosc (L): " << getL() << endl;
	cout << "Powierzchnia (S): " << getS() << endl;
	cout << "Wspolczynnik przewodzenia ciepla (K): " << getK() << endl;
	cout << "Q (q): " << getQ() << endl;
	cout << "Alfa (alfa): " << getAlfa() << endl;
	cout << "Temperatura: " << getT() << endl;
}

void GlobalData::tworzGlobalnaMacierzH(int wymiar)
{
	this->H_globalne = new double*[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		H_globalne[i] = new double[wymiar+1];
	}

	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
			H_globalne[i][j] = 0;
	}

}

void GlobalData::tworzGlobalnyWektorP(int wymiar)
{
	this->P_globalne = new double[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		P_globalne[i] = 0;
	}
}

void GlobalData::wypiszHg()
{
	cout << endl;
	for (int i = 0; i < this->getMn(); i++)
	{
		for (int j = 0; j <= this->getMn(); j++)
		{
			cout << this->H_globalne[i][j] << " ";
		}
		cout << endl;
	}
}

void GlobalData::wypiszPg()
{
	cout << endl;
	for (int j = 0; j < this->getMn(); j++)
	{
		cout << this->P_globalne[j] << " ";
	}
	cout << endl;

}

void GlobalData::wypiszWektorT()
{
	for (int i = 0; i < Mn; i ++)
	{ 
		cout << "t" << i << " " << WektorT[i] << endl;
	}
	std::fstream plik("wynik.txt", std::ios::out);
	if (plik.good() == true)
	{
		for (int i = 0; i < Mn; i++)
		plik<< "t" << i << " " << WektorT[i] << endl;
		plik.close();
	}


}

void GlobalData::setMe(int n)
{
	this->Me = n;
}
void GlobalData::setMn(int n)
{
	this->Mn = n;
}
void GlobalData::setL(double n)
{
	this->L = n;
}
void GlobalData::setS(double n)
{
	this->S = n;
}
void GlobalData::setK(double n)
{
	this->K = n;
}

void GlobalData::setQ(double q)
{
	this->q = q;
}

void GlobalData::setAlfa(double alfa)
{
	this->alfa = alfa;
}

void GlobalData::setT(double T)
{
	this->T = T;
}

void GlobalData::setWektorT(double* T)
{
	this->WektorT = T;
}


void GlobalData::tworzWektorT(int wymiar)
{
	this->WektorT = new double[wymiar];
	for (int i = 0; i < wymiar; i++)
	{
		this->WektorT[i] = 0.0;
	}
}

void GlobalData::free()
{
	for (int i = 0; i < this->getMn(); i++)
		{
			delete[] H_globalne[i];
		}
	delete[] H_globalne;
	delete[] P_globalne;
	delete[] WektorT;
}

int GlobalData::getMe()
{
	return Me;
}

int GlobalData::getMn()
{
	return Mn;
}

double GlobalData::getL()
{
	return L;
}

double GlobalData::getS()
{
	return S;
}

double GlobalData::getK()
{
	return K;
}

double GlobalData::getQ()
{
	return (this->q);
}

double GlobalData::getAlfa()
{
	return (this->alfa);
}

double GlobalData::getT()
{
	return (this->T);
}

double** GlobalData::getH_globalne()
{
	// cout << endl<< H_globalne << endl;  adres OK
	return (this->H_globalne);
}

double* GlobalData::getP_globalne()
{
	return (this->P_globalne);
}

double* GlobalData::getWektorT()
{
	return (this->WektorT);
}