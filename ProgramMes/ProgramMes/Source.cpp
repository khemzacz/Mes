#include <iostream>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <string>
#include "GlobalData.h"

using namespace std;

GlobalData* globaldata;


int main()
{
	globaldata = new GlobalData();
	globaldata->pobierz_dane();
	globaldata->wypisz_dane();

	system("PAUSE");

	return 0;
}