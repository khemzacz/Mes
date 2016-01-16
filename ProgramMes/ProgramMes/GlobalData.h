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
	void setk(double n);
	void setQ(double q);
	void setAlfa(double alfa);
	void setT(double T);
	void setrMax(double);
	void setdeltaR(double);
	void setdeltaTau(double);
	void setc(double);
	void setp(double);
	void sett0(double);
	void settn(double);

	int getMe();
	int getMn();
	double getL();
	double getS();
	double getk();
	double getQ();
	double getAlfa();
	double getT();
	double getrMax();
	double getdeltaR();
	double getdeltaTau();
	double getc();
	double getp();
	double gett0();
	double gettn();

	void pobierz_dane();
	void wypisz_dane();


private:
	int Me, Mn;
	double L, S, k; // 
	double q, alfa, T; // 
	double rMax, deltaR, deltaTau, c, p, t0, tn;
};

