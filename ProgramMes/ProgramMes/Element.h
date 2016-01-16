#pragma once
#include"Node.h"
#include"GlobalData.h"

class Element
{
public:
	Element(long, long, long, double L, int Me);
	Element();
	~Element();

	void setH_lokalne(double wartosc, int w, int k);
	void setP_lokalne(double wartosc, int k);
	void setGlobalData(GlobalData*);
	

	double getDl();
	double** getH_lokalne();
	double* getP_lokalne();

	double** getK_lokalne();
	void setNOP1(Node*);
	void setNOP2(Node*);

	void createK_lokalne();
	void calculateK_lokalne();

	double calkowanie_jeden();

	GlobalData* getGlobalData();
	void free();

private:
	long ID;
	Node* NOP1;
	Node* NOP2;
	double dl;
	double S;
	//double k;

	double** K_lokalne;

	GlobalData* gb;
	double** H_lokalne;
	double* P_lokalne;
};

