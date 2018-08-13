////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "genetico.h"
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
	int tamNosotros;
	int tamEllos;
	cin >> tamNosotros;
	cin >> tamEllos;

	int cantidadPoblacion = tamNosotros;
	int cantidadGenes = 15;
	int cantidadGeneraciones = 10;
	int porcPoblacionQueMuta = 1;
	int porcMutacion = 10;

    genetico trainerMejores = genetico(cantidadPoblacion, cantidadGenes, cantidadGeneraciones, porcPoblacionQueMuta, porcMutacion);
	trainerMejores.entrenarAux(tamNosotros, tamEllos);

    return 0;
};
