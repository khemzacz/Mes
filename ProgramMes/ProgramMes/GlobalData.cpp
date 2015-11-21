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