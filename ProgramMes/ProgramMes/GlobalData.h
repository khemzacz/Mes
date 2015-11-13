#pragma once
class GlobalData
{
public:
	GlobalData();
	~GlobalData();

	void set_Me(int n);
	void set_Mn(int n);
	void set_L(double n);
	void set_S(double n);
	void set_K(double n);
	int get_Me();
	int get_Mn();
	double get_L();
	double get_S();
	double get_K();
	
	void pobierz_dane();
	void wypisz_dane();
	
private:
	int Me, Mn;
	double L, S, K;


};

