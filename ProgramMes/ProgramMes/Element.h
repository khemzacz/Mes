#pragma once
#include"Node.h"
#include"GlobalData.h"

class Element
{
public:

	Element();
	~Element();

	void setGlobalData(GlobalData*);
	

	double getDl();


	double** getK_lokalne();
	double* getF_lokalne();
	void setNOP1(Node*);
	void setNOP2(Node*);
	void setID(int);

	void createK_lokalne();
	void createF_lokalne();
	void calculateLocalMatricies();

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
	double* F_lokalne;

	GlobalData* gb;
};

