#include "FEM_GRID.h"
#include "source.h"
#include "GlobalData.h"
#include "Node.h"


FEM_GRID::FEM_GRID()
{
}


FEM_GRID::~FEM_GRID()
{
}

void FEM_GRID::generateFEM_GRID()
{
	elementy = new Element*[globaldata->get_Me()];
	wezly = new Node*[globaldata->get_Mn];
	/* tworze elementy i wezly */
	for (int i = 0; i < globaldata->get_Me();i++)
	{
		elementy[i] = new Element();
	}

	for (int i = 0; i < globaldata->get_Mn(); i++)
	{
		wezly[i] = new Node();
	}


	/* tutaj wpisuje elementom wezly */


}
