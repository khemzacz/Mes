#include "Element.h"



Element::Element(long ID, long NOP1, long NOP2, double L, int Me)
{
	this->ID = ID;
	this->NOP1 = NOP1;
	this->NOP2 = NOP2;

	H_lokalne = new double*[2];

	this->dl = L / Me;

	for (int i = 0; i < 2; i++)
	{
		H_lokalne[i] = new double[2];
	}

	P_lokalne = new double[2];
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

double* Element::getP_lokalne()
{
	return (this->P_lokalne);
}