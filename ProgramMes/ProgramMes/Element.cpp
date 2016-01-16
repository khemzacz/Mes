#include <iostream>
#include "Element.h"

using namespace std;

Element::Element(long ID, long NOP1, long NOP2, double L, int Me)
{
	this->ID = ID;

	H_lokalne = new double*[2];

	this->dl = L / Me;

	for (int i = 0; i < 2; i++)
	{
		H_lokalne[i] = new double[2];
	}

	P_lokalne = new double[2];
}

Element::Element()
{
}


Element::~Element()
{
}


double Element::getDl()
{
	return (this->dl);
}

double** Element::getH_lokalne()
{
	return (this->H_lokalne);
}

void Element::setH_lokalne(double wartosc, int w, int k)
{
	this->H_lokalne[w][k] = wartosc;
}

void Element::setP_lokalne(double wartosc, int k)
{
	this->P_lokalne[k] = wartosc;
}



void Element::free()
{

}

double* Element::getP_lokalne()
{
	return (this->P_lokalne);
}

double ** Element::getK_lokalne()
{
	return this->K_lokalne;
}

void Element::setNOP1(Node * sample_node)
{
	this->NOP1 = sample_node;
}

void Element::setNOP2(Node * sample_node)
{
	this->NOP2 = sample_node;
}

void Element::createK_lokalne()
{
	K_lokalne = new double*[2];
	for (int i = 0; i < 2; i++)
	{
		K_lokalne[i] = new double[2];
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			K_lokalne[i][j] = 0.0;
		}
}

void Element::calculateK_lokalne()
{
	double wynik_calkowania = 0;
	
	


	double c = gb->getc();
	double deltaR = gb->getdeltaR();
	double deltaTau = gb->getdeltaTau();
	double k = gb->getk();
	// Schemat ca?kowania dwópunktowy: -0.57735, 0.57735 wagi = 1
	double rp1 = (0.5*(1 - 0.5773502692)*gb->getdeltaR()+NOP1->getr());
	double rp2 = NOP1->getr()+0.5*gb->getdeltaR()+0.5*gb->getdeltaR()*0.5773502692;
	double E[2] = { -0.5773502692, 0.5773502692 };
	double N1[2] = { 0.5*(1 - E[0]), 0.5*(1 - E[1]) };
	double N2[2] = { 0.5*(1 + E[0]), 0.5*(1 + E[1]) };
	double rp;

	double p = gb->getp();
	double waga = 1;
	// cout << endl << rp; // wyglada rozsadnie
	for (int i = 0; i < 2; i++)
	{
		rp = ( N1[i] * NOP1->getr() + N2[i] * NOP2->getr() );
		//cout << endl << rp << endl; ok
		K_lokalne[0][0] += k*rp*waga / deltaR + c*p*deltaR*rp*waga*N1[i] * N1[i] / deltaTau;

		K_lokalne[0][1] = -1 * gb->getk() / gb->getdeltaR() *(rp1 + rp2);

		K_lokalne[1][0];

		K_lokalne[1][1] = k / deltaR;
	}
	cout << endl << K_lokalne[0][0];
}

double Element::calkowanie_jeden() //schematem trójpunktowym
{
	double suma_local = 0;

	suma_local += -0.7796*0.625;
	suma_local += 0 * 0.888;
	suma_local += 7796 * 0.625;


	return suma_local;
}

void Element::setGlobalData(GlobalData* sample)
{
	this->gb = sample;
}

GlobalData * Element::getGlobalData()
{
	return this->gb;
}
