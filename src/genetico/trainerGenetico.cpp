////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "genetico.h"
#include <chrono>

using namespace std;

int main(int argc,char *argv[])
{
    int fitness = 2;
    int selection = 1;
	int crossover = 1;

    if(argc > 1)
        fitness = atoi(argv[1]);
    if(argc > 2)
        selection = atoi(argv[2]);
    if(argc > 3)
        selection = atoi(argv[3]);

	int cantidadPoblacion = 16 ; //DEBE SER MULTIPLO DE 4
	int cantidadGenes = 15;
	int cantidadGeneraciones = 10;
	int porcPoblacionQueMuta = 1;
	int porcMutacion = 30;

    genetico trainerGenetico = genetico(cantidadPoblacion, cantidadGenes, cantidadGeneraciones, porcPoblacionQueMuta, porcMutacion);

	cout << "Busca el mejor con cantidad poblacion: " << cantidadPoblacion << " y con " << cantidadGeneraciones << " generaciones ..." << endl;

    auto startGenetico = chrono::steady_clock::now();

    genoma elMejor = trainerGenetico.entrenar(fitness, selection, crossover);

    auto endGenetico = chrono::steady_clock::now();

    auto diffGenetico = endGenetico - startGenetico;

    cout << "Tiempo de entrenamiento:"<< chrono::duration <double, milli> (diffGenetico).count() << endl;

	cout << "El algoritmo genetico encontro este: " << endl;

    elMejor.imprimirGenoma();

    return 0;
};
