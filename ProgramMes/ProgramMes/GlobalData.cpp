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

bool GlobalData::pobierz_dane()
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
			else if (test == "k:")
			{
				setk(wartosc);
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
			else if (test == "rMax:")
			{
				setrMax(wartosc);
			}
			else if (test == "deltaR:")
			{
				setdeltaR(wartosc);
			}
			else if (test == "deltaTau:")
			{
				setdeltaTau(wartosc);
			}
			else if (test == "c:")
			{
				setc(wartosc);
			}
			else if (test == "p:")
			{
				setp(wartosc);
			}
			else if (test == "t0:")
			{
				sett0(wartosc);
			}
			else if (test == "tn:")
			{
				settn(wartosc);
			}
			else if (test == "TauMax:")
			{
				setTauMax(wartosc);
			}

			//cout << test << "\t" << wartosc << endl;
		}
		plik.close();
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void GlobalData::wypisz_dane()
{
	cout <<endl<< "Liczba Elementow (Me): " << getMe()<<endl;
	cout << "Liczba Wezlow (Mn): " << getMn() << endl;
	//cout << "DLugosc (L): " << getL() << endl;
	//cout << "Powierzchnia (S): " << getS() << endl;
	cout << "Wspolczynnik przewodzenia ciepla (K): " << getk() << endl;
	//cout << "Q (q): " << getQ() << endl;
	cout << "Alfa (alfa): " << getAlfa() << endl;
	cout << "Temperatura: " << getT() << endl;
	cout << "rMax: " << getrMax() << "\t" ;
	cout << "deltaR: " << getdeltaR() << "\t";
	cout << "deltaTau: " << getdeltaTau() << endl;
	cout << "c: " << getc() << "\t";
	cout << "p: " << getp() << "\t";
	cout << "k: " << getk() << endl;
	cout << "t0: " << gett0() << "\t";
	cout << "tn: " << gettn() << "\t";
	cout << "TauMax: " << getTauMax() << "\t";



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
void GlobalData::setk(double n)
{
	this->k = n;
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

void GlobalData::setrMax(double sample_var)
{
	this->rMax = sample_var;
}

void GlobalData::setdeltaR(double sample_var)
{
	this->deltaR = sample_var;
}

void GlobalData::setdeltaTau(double sample_var)
{
	this->deltaTau = sample_var;
}

void GlobalData::setc(double sample_var)
{
	this->c = sample_var;
}

void GlobalData::setp(double sample_var)
{
	this->p = sample_var;
}

void GlobalData::sett0(double sample_var)
{
	this->t0 = sample_var;
}

void GlobalData::settn(double sample_var)
{
	this->tn = sample_var;
}

void GlobalData::setTauMax(double sample)
{
	this->TauMax = sample;
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

double GlobalData::getk()
{
	return k;
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

double GlobalData::getrMax()
{
	return (this->rMax);
}

double GlobalData::getdeltaR()
{
	return (this->deltaR);
}

double GlobalData::getdeltaTau()
{
	return (this->deltaTau);;
}

double GlobalData::getc()
{
	return (this->c);
}

double GlobalData::getp()
{
	return (this->p);
}

double GlobalData::gett0()
{
	return (this->t0);
}

double GlobalData::gettn()
{
	return (this->tn);
}

double GlobalData::getTauMax()
{
	return this->TauMax;
}



