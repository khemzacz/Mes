#pragma once
class GlobalData
{
public:
	GlobalData();
	~GlobalData();

	void setMe(int n);
	void setMn(int n);
	void setL(double n);
	void setS(double n);
	void setK(double n);
	void setQ(double q);
	void setAlfa(double alfa);
	void setT(double T);
	int getMe();
	int getMn();
	double getL();
	double getS();
	double getK();
	double getQ();
	double getAlfa();
	double getT();


	double** getH_globalne();
	double* getP_globalne();
	double* getWektorT();

	void pobierz_dane();
	void wypisz_dane();
	void tworzGlobalnaMacierzH(int wymiar);
	void tworzGlobalnyWektorP(int wymiar);
	void tworzWektorT(int wymiar);

private:
	int Me, Mn;
	double L, S, K;
	double q, alfa, T;

	double** H_globalne;
	double* P_globalne;
	double* WektorT;
};

