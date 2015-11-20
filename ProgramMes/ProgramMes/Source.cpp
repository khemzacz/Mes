#include <iostream>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <string>
#include "GlobalData.h"
#include "Source.h"

using namespace std;




int main()
{
	globaldata = new GlobalData();
	globaldata->pobierz_dane();
	globaldata->wypisz_dane();

	system("PAUSE");

	return 0;
}