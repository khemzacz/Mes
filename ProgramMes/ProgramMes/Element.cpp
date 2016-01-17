#include <iostream>
#include "Element.h"

using namespace std;



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





void Element::free()
{
	for (int i = 0; i < 2; i++)
		delete[] K_lokalne[i];
	delete[] K_lokalne;
	delete[] F_lokalne;
}



double ** Element::getK_lokalne()
{
	return this->K_lokalne;
}

double * Element::getF_lokalne()
{
	return this->F_lokalne;
}

void Element::setNOP1(Node * sample_node)
{
	this->NOP1 = sample_node;
}

void Element::setNOP2(Node * sample_node)
{
	this->NOP2 = sample_node;
}

void Element::setID(int sample_int)
{
	this->ID = sample_int;
}

void Element::createK_lokalne()
{
	K_lokalne = new double*[2];
	for (int i = 0; i < 2; i++)
	{
		K_lokalne[i] = new double[2];
	}

}

void Element::createF_lokalne()
{
	F_lokalne = new double[2];

}

void Element::calculateLocalMatricies(double deltaTau)
{
	for (int i = 0; i < 2; i++) /*Zerowanie*/
		for (int j = 0; j < 2; j++)
		{
			K_lokalne[i][j] = 0.0;
		}
	F_lokalne[0] = 0.0; F_lokalne[1] = 0.0; /*Zerowanie*/
	


	double c = gb->getc();
	double deltaR = gb->getdeltaR();
	//double deltaTau = gb->getdeltaTau();
	double k = gb->getk();
	// Schemat ca?kowania dwópunktowy: -0.57735, 0.57735 wagi = 1
	double rp1 = (0.5*(1 - 0.5773502692)*gb->getdeltaR()+NOP1->getr());
	double rp2 = NOP1->getr()+0.5*gb->getdeltaR()+0.5*gb->getdeltaR()*0.5773502692;
	double E[2] = { -0.5773502692, 0.5773502692 };
	double N1[2] = { 0.5*(1 - E[0]), 0.5*(1 - E[1]) };
	double N2[2] = { 0.5*(1 + E[0]), 0.5*(1 + E[1]) };
	double rp,tptau;

	double p = gb->getp();
	double waga = 1;
	// cout << endl << rp; // wyglada rozsadnie
	double alfa = 0.0;
	if (this->ID == gb->getMe())
		alfa = gb->getAlfa();
	for (int i = 0; i < 2; i++)
	{
		rp = ( N1[i] * NOP1->getr() + N2[i] * NOP2->getr() );
		tptau = ( N1[i] * NOP1->getTemp() + N2[i] * NOP2->getTemp() ); 
		K_lokalne[0][0] += k*rp*waga / deltaR + c*p*deltaR*rp*waga*N1[i] * N1[i] / deltaTau;

		K_lokalne[0][1] += -1* k*rp*waga / deltaR + c*p*deltaR*rp*waga*N1[i] * N2[i] / deltaTau;

		K_lokalne[1][0] = K_lokalne[0][1];

		K_lokalne[1][1] += k*rp*waga / deltaR +  c*p*deltaR*rp*waga*N2[i] * N2[i] / deltaTau ;

		F_lokalne[0] += c*p*deltaR*tptau*rp*waga*N1[i] / deltaTau;

		F_lokalne[1] += c*p*deltaR*tptau*rp*waga*N2[i] / deltaTau ;

	}
	F_lokalne[1] += 2 * alfa*gb->getrMax()*gb->gettn();
	K_lokalne[1][1] += 2 * alfa*gb->getrMax();
	//cout << endl << K_lokalne[0][0];
	//cout << endl << K_lokalne[0][1];
	//cout << endl << K_lokalne[1][0];
	//cout << endl << K_lokalne[1][1]<<endl;
	//cout << endl << F_lokalne[0];
	//cout << endl << F_lokalne[1] << endl;

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
