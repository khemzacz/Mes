#pragma once
#include"Node.h"

class Element
{
public:
	Element(long, long, long, double L, int Me);
	~Element();

	void setH_lokalne(double wartosc, int w, int k);

	double getDl();
	double** getH_lokalne();



private:
	long ID;
	long NOP1;
	long NOP2;
	double dl;
	double S;
	double K;
	double** H_lokalne;
	double P_lokalne[2];
};

