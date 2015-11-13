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
				set_Me((int)wartosc);
			}
			else if (test == "Mn:")
			{
				set_Mn((int)wartosc);
			}
			else if (test == "L:")
			{
				set_L(wartosc);
			}
			else if (test == "S:")
			{
				set_S(wartosc);
			}
			else if (test == "K:")
			{
				set_K(wartosc);
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
	cout <<endl<< "Liczba Elementow (Me): " << get_Me()<<endl;
	cout << "Liczba Wezlow (Mn): " << get_Mn() << endl;
	cout << "DLugosc (L): " << get_L() << endl;
	cout << "Powierzchnia (S): " << get_S() << endl;
	cout << "Wspolczynnik przewodzenia ciepla (K): " << get_K() << endl;
}

void GlobalData::set_Me(int n)
{
	Me = n;
}
void GlobalData::set_Mn(int n)
{
	Mn = n;
}
void GlobalData::set_L(double n)
{
	L = n;
}
void GlobalData::set_S(double n)
{
	S = n;
}
void GlobalData::set_K(double n)
{
	K = n;
}

int GlobalData::get_Me()
{
	return Me;
}

int GlobalData::get_Mn()
{
	return Mn;
}

double GlobalData::get_L()
{
	return L;
}

double GlobalData::get_S()
{
	return S;
}

double GlobalData::get_K()
{
	return K;
}