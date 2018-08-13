////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include "../../lib/genoma.h"

using namespace std;

class genetico
{

	public:

		genetico(int cantidadPoblacion, int cantidadGenes, int cantidadGeneraciones, int porcPoblacionQueMuta, int porcMutacion);
		genoma entrenar(int fitness, int seleccion, int crossover);
		void entrenarAux(int tamNosotros, int tamEllos);

	private:

		int cantidadPoblacion_;
		int cantidadGenes_;
		int maxGeneraciones_;
		int porcPoblacionQueMuta_;
		int porcMutacion_;

		int generacion_;
		vector<genoma> poblacion_;

		void generarGenomaRandom(genoma &g);
		void evaluarPoblacion(int fitness);
		void mutacion();
		void printStatus();

		void generarPoblacion();
		void fitness_1();
		void fitness_1Aux(vector<genoma> &ellos);
		void fitness_2(int cantJugadas);
		void crossover_1(genoma padre, genoma madre, genoma &hijo1, genoma &hijo2);
		void crossover_2(genoma padre, genoma madre, genoma &hijo1, genoma &hijo2);
		void reproduccion_random(int crossover);
		void reproduccion_selectiva(int crossover);
		genoma mutar(genoma g);

		static bool compararGenoma_(genoma g1,genoma g2){return (g1.puntaje() > g2.puntaje());}


};
