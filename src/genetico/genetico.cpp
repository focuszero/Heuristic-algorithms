////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "genetico.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <chrono>


using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR Y AUXILIARES DE LA CLASE ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

genetico::genetico(int cantidadPoblacion, int cantidadGenes, int cantidadGeneraciones, int porcPoblacionQueMuta, int porcMutacion)
{
	cantidadPoblacion_ = cantidadPoblacion;
	cantidadGenes_ = cantidadGenes + 3;
	maxGeneraciones_ = cantidadGeneraciones;
	porcPoblacionQueMuta_ = porcPoblacionQueMuta;
	porcMutacion_ = porcMutacion;
	generacion_ = 0;
}

void genetico::generarGenomaRandom(genoma &g)
{
	for(int i = 0; i < cantidadGenes_; i++)
	{
		int rndGen = (rand() % 201) - 100;
		g.agregarGen(rndGen);
	}
}

void genetico::evaluarPoblacion(int fitness)
{
	for(int i = 0; i < cantidadPoblacion_; i++)
	{
		poblacion_[i].limpiarPartidos();
	}

	if(fitness == 1)
		fitness_1();
	else
		fitness_2(3);
}

void genetico::mutacion()
{
	for(int i = 0; i < cantidadPoblacion_; i++)
	{
		int mutacion = rand() % 100 + 1;
		if(mutacion <= porcPoblacionQueMuta_)
			poblacion_[i] = mutar(poblacion_[i]);
	}
}

void genetico::printStatus()
{
	for(int i = 0; i < cantidadPoblacion_; i++)
	{
		cout << "GENOMA NUMERO " << i << " ";
		poblacion_[i].imprimirGenoma();
		cout << "	Donde jugo: " << poblacion_[i].partidos() << " partidos y gano: " << poblacion_[i].ganados() << ", perdio: " << poblacion_[i].perdidos() << ", empatados: " << poblacion_[i].empatados() << endl << endl;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
// GENETICO ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void genetico::generarPoblacion()
{
	for(int i = 0; i < cantidadPoblacion_; i++)
	{
		genoma gen = genoma();
		generarGenomaRandom(gen);
		poblacion_.push_back(gen);
	}
}

void genetico::fitness_1()
{
	for(int j = 0; j < cantidadPoblacion_; j++)
	{
		for(int i = j+1; i < cantidadPoblacion_; i++)
		{
			int alto = 10;
			int ancho = 5;
			int steps = 35;
			bool azul = rand() % 2;
 			bool primeroAzul = rand() % 2;
            int resultado = poblacion_[j].play(poblacion_[i], azul, alto, ancho, steps, primeroAzul);

            if(resultado == 3)
			{
				poblacion_[j].incGanados();
				poblacion_[i].incPerdidos();
			}
            else if(resultado == 0)
			{
				poblacion_[j].incPerdidos();
				poblacion_[i].incGanados();
			}
			else
			{
				poblacion_[j].incEmpatados();
				poblacion_[i].incEmpatados();
			}
		}
	}
}

void genetico::fitness_1Aux(vector<genoma> &ellos)
{
	for(int j = 0; j < cantidadPoblacion_; j++)
	{
		for(int i = 0; i < ellos.size(); i++)
		{
			int alto = 10;
			int ancho = 5;
			int steps = 50;
			bool azul = rand() % 2;
 			bool primeroAzul = rand() % 2;
            int resultado = poblacion_[j].play(ellos[i], azul, alto, ancho, steps, primeroAzul);

            if(resultado == 3)
			{
				poblacion_[j].incGanados();
				ellos[i].incPerdidos();
			}
            else if(resultado == 0)
			{
				poblacion_[j].incPerdidos();
				ellos[i].incGanados();
			}
			else
			{
				poblacion_[j].incEmpatados();
				ellos[i].incEmpatados();
			}
		}
	}
}

void genetico::fitness_2(int cantJugadas)
{
	set<int> clasificados;
	for(int i = 0; i < cantidadPoblacion_; i++)
	{
		clasificados.insert(i);
	}
	for(int i = cantidadPoblacion_; i > 1; i = i/2)
	{
		auto it = clasificados.begin();
		int contador = 0;
		while(contador != i)
		{
			auto it2 = it;
			it2++;
			int itGanados = 0;
			int it2Ganados = 0;
			for(int j = 0; j < cantJugadas; j++)
			{
				int alto = 10;
				int ancho = 5;
				int steps = 35;
				bool azul = rand() % 2;
	 			bool primeroAzul = rand() % 2;
            	int resultado = poblacion_[(*it)].play(poblacion_[(*it2)], azul, alto, ancho, steps, primeroAzul);

            	if(resultado == 3)
	 			{
	 				itGanados++;
	 				poblacion_[(*it)].incGanados();
	 				poblacion_[(*it2)].incPerdidos();
	 			}
            	else if(resultado == 0)
	 			{
	 				it2Ganados++;
	 				poblacion_[(*it)].incPerdidos();
	 	     		poblacion_[(*it2)].incGanados();
	 			}
	 			else
	 			{
	 				poblacion_[(*it)].incEmpatados();
	 				poblacion_[(*it2)].incEmpatados();
	 			}
			}

			auto itAux = it;
			itAux++;
			itAux++;
			if(itGanados < it2Ganados)
			{
				clasificados.erase((*it));
			}
			else if(itGanados > it2Ganados)
			{
				clasificados.erase((*it2));
			}
			else
			{
				int clasificoRandom = rand() % 2;
				if(clasificoRandom == 0)
				{
					clasificados.erase((*it));
				}
				else
				{
					clasificados.erase((*it2));
				}
			}
			it = itAux;
			contador = contador + 2;
		}
	}
}

void genetico::crossover_1(genoma padre, genoma madre, genoma &hijo1, genoma &hijo2)
{
	int hastaPadre;

	if(padre.puntaje() > madre.puntaje())
		hastaPadre = (cantidadGenes_/4)*3;

	else if(padre.puntaje() < madre.puntaje())
		hastaPadre = cantidadGenes_/4;

	else
		hastaPadre = cantidadGenes_/2;

	for(int i = 0; i < hastaPadre; i++)
		hijo1.agregarGen(padre.genes()[i]);

	for(int i = hastaPadre; i < cantidadGenes_; i++)
		hijo1.agregarGen(madre.genes()[i]);

	for(int i = 0; i < hastaPadre; i++)
		hijo2.agregarGen(madre.genes()[i]);

	for(int i = hastaPadre; i < cantidadGenes_; i++)
		hijo2.agregarGen(padre.genes()[i]);
}

void genetico::crossover_2(genoma padre, genoma madre, genoma &hijo1, genoma &hijo2)
{
	for(int i = 0; i < cantidadGenes_; i++)
	{
		int genLoteria1 = rand() % 2;
		int genLoteria2 = rand() % 2;
		if(genLoteria1 == 0)
			hijo1.agregarGen(padre.genes()[i]);
		else
			hijo1.agregarGen(madre.genes()[i]);

		if(genLoteria2 == 0)
			hijo2.agregarGen(padre.genes()[i]);
		else
			hijo2.agregarGen(madre.genes()[i]);

	}
}

void genetico::reproduccion_random(int crossover)
{
	vector<genoma> poblacionNueva;

	vector<bool> disponible(cantidadPoblacion_,true);
	for(int i = 0; i < (cantidadPoblacion_/2); i++)
	{
		genoma hijo1 = genoma();
		genoma hijo2 = genoma();

		int padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[padre])
		// 	padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[padre] = false;

		int madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[madre])
		// 	madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[madre] = false;


		if(crossover == 1)
			crossover_1(poblacion_[padre], poblacion_[madre], hijo1, hijo2);
		else
			crossover_2(poblacion_[padre], poblacion_[madre], hijo1, hijo2);

		poblacionNueva.push_back(hijo1);
		poblacionNueva.push_back(hijo2);
	}

	poblacion_ = poblacionNueva;
}

void genetico::reproduccion_selectiva(int crossover)
{
	vector<genoma> poblacionNueva;

	sort(poblacion_.begin(), poblacion_.end(), compararGenoma_);

	for(int i = 0; i < (cantidadPoblacion_/4);i++)
	{
		poblacionNueva.push_back(poblacion_[i]);
	}

	vector<bool> disponible(cantidadPoblacion_,true);
	for(int i = 0; i < (cantidadPoblacion_/4);i++)
	{
		genoma hijo1 = genoma();
		genoma hijo2 = genoma();
		genoma hijo3 = genoma();

		int padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[padre])
		// 	padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[padre] = false;

		int madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[madre])
		// 	madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[madre] = false;

		if(crossover == 1)
			crossover_1(poblacion_[padre], poblacion_[madre], hijo1, hijo2);
		else
			crossover_2(poblacion_[padre], poblacion_[madre], hijo1, hijo2);

		poblacionNueva.push_back(hijo1);
		poblacionNueva.push_back(hijo2);

		padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[padre])
		// 	padre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[padre] = false;

		madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// while(!disponible[madre])
		// 	madre = rand() % (cantidadPoblacion_ - cantidadPoblacion_/4);
		// disponible[madre] = false;

		if(crossover == 1)
			crossover_1(poblacion_[padre], poblacion_[madre], hijo3, hijo2);
		else
			crossover_2(poblacion_[padre], poblacion_[madre], hijo3, hijo2);

		poblacionNueva.push_back(hijo3);
	}

	poblacion_ = poblacionNueva;
}

genoma genetico::mutar(genoma g)
{
	int cuantosGenesMutan = rand() % (cantidadGenes_ * porcMutacion_ / 100);

	vector<int> genes = g.genes();
	for(int i = 0; i < cuantosGenesMutan; i++)
	{
		int genMuta = rand() % cantidadGenes_;
		int rndGen = (rand() % 201) - 100;

		genes[genMuta] = rndGen;
	}
	g.cargarGenes(genes);

	return g;
}

////////////////////////////////////////////////////////////////////////////////
// TREINER GENETICO ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

genoma genetico::entrenar(int fitness, int seleccion, int crossover)
{
	srand(time(NULL));
	genoma elMejor = genoma();
	generacion_ = 0;

	cout << "GENERO POBLACION" << endl << endl;
	generarPoblacion();
	printStatus();

	cout << "EVALUO POBLACION" << endl << endl;
	auto startEvaluar = chrono::steady_clock::now();
	evaluarPoblacion(fitness);
	auto endEvaluar = chrono::steady_clock::now();
	printStatus();

	auto diffEvaluar = endEvaluar - startEvaluar;
	cout << "Tiempo de evaluacion:"<< chrono::duration <double, milli> (diffEvaluar).count() << endl;

	cout << "EMPIEZO CICLO" << endl;
	auto startCiclo = chrono::steady_clock::now();
	while(generacion_ != maxGeneraciones_)
	{
		cout << "PROCESO DE SELECCION" << endl << endl;
		auto startSeleccion = chrono::steady_clock::now();
		if(seleccion == 1)
			reproduccion_selectiva(crossover);
		else
			reproduccion_random(crossover);
		auto endSeleccion = chrono::steady_clock::now();
		printStatus();

		cout << "MUTO POBLACION" << endl << endl;
		auto startMutar = chrono::steady_clock::now();
		mutacion();
		auto endMutar = chrono::steady_clock::now();
		printStatus();

		cout << "EVALUO POBLACION" << endl << endl;
		auto startEvaluarPoblacion = chrono::steady_clock::now();
		evaluarPoblacion(fitness);
		auto endEvaluarPoblacion = chrono::steady_clock::now();
		printStatus();

		cout << "MUESTRO MAXIMO OBTENIDO" << endl << endl;
		int max = 0;
		for(int i = 0; i < cantidadPoblacion_; i++)
		{
			if(poblacion_[i].puntaje() > poblacion_[max].puntaje())
				max = i;
		}

		elMejor = poblacion_[max];

		cout << "Generacion: " << generacion_+1 << " el puntaje max es: " << poblacion_[max].puntaje() << endl;
		cout << "Donde jugo: " << poblacion_[max].partidos() << " partidos y gano: " << poblacion_[max].ganados() << ", perdio: " << poblacion_[max].perdidos() << ", empatados: " << poblacion_[max].empatados() << endl;
		cout << "De los cuales ";
		poblacion_[max].imprimirGenoma();

		auto diffSeleccion = endSeleccion - startSeleccion;
		cout << "Tiempo de seleccion:"<< chrono::duration <double, milli> (diffSeleccion).count() << endl;
		auto diffMutar = endMutar - startMutar;
		cout << "Tiempo de mutar:"<< chrono::duration <double, milli> (diffMutar).count() << endl;
		auto diffEvaluarPoblacion = endEvaluarPoblacion - startEvaluarPoblacion;
		cout << "Tiempo de evaluar poblacion:"<< chrono::duration <double, milli> (diffEvaluarPoblacion).count() << endl;

		cout << endl << "--------------------------------------------------------------------------------------------------------------------" << endl << endl;
		generacion_++;
	}
	auto endCiclo = chrono::steady_clock::now();
	auto diffCiclo = endCiclo - startCiclo;
	cout << "Tiempo total del CICLO:"<< chrono::duration <double, milli> (diffCiclo).count() << endl;

	return elMejor;
}

////////////////////////////////////////////////////////////////////////////////
// TREINER AUXILIAR ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void genetico::entrenarAux(int tamNosotros, int tamEllos)
{
	for (int i = 0; i < tamNosotros; ++i)
	{
		genoma gen = genoma();
		int k;
		float f;
		for (int j = 0; j < 18; ++j)
		{
			if(j == 15 or j == 16 or j == 17)
			{
				cin >> f;
				k = f*100;
			}
			else
				cin >> k;

			gen.agregarGen(k);
		}
		poblacion_.push_back(gen);
	}

	vector<genoma> ellos;
	for (int i = 0; i < tamEllos; ++i)
	{
		genoma gen = genoma();
		int k;
		float f;
		for (int j = 0; j < 18; ++j)
		{
			if(j == 15 or j == 16 or j == 17)
			{
				cin >> f;
				k = f*100;
			}
			else
				cin >> k;

			gen.agregarGen(k);
		}
		ellos.push_back(gen);
	}

	fitness_1Aux(ellos);

	cout << "Los del equipo A:" << endl;
	for (int i = 0; i < tamNosotros; ++i)
	{
	    cout << "Puntajes del " << "equipo " << i  << "partidos jugados:" << poblacion_[i].partidos() << "gano:" << poblacion_[i].ganados() << "perdio:" << poblacion_[i].perdidos() << "empato:" << poblacion_[i].empatados() << "puntaje:" << poblacion_[i].puntaje() << endl;
	}
	
	cout << "--------------------------------------------------------------------------" << endl;

	cout << "Los del equipo B:" << endl;
	for (int i = 0; i < tamEllos; ++i)
	{
	    cout << "Puntajes del " << i << "equipo:" << "partidos jugados:" << ellos[i].partidos() << "gano:" << ellos[i].ganados() << "perdio:" << ellos[i].perdidos() << "empato:" << ellos[i].empatados() << "puntaje:" << ellos[i].puntaje() << endl;
	}
}
