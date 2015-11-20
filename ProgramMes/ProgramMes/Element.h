#pragma once
#include"Node.h"

class Element
{
public:
	Element(long, long, long);
	~Element();


private:
	long ID;
	long NOP1;
	long NOP2;
	double dl;
	double S;
	double K;
	double H__lokalne[2][2];
	double P_lokalne[1][2];
};

