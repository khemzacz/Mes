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
	int getMe();
	int getMn();
	double getL();
	double getS();
	double getK();
	double getQ();
	double getAlfa();
	
	void pobierz_dane();
	void wypisz_dane();
	
private:
	int Me, Mn;
	double L, S, K;
	double q, alfa;


};

