////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "../src/player.h"
#include <time.h>

using namespace std;

class genoma
{

	public:

		genoma();
		vector<int> genes();
		int puntaje();
		void agregarGen(int gen);
		void otorgarPuntaje(int puntaje);
		void cargarGenes(vector<int> genes);

		int partidos();
		int ganados();
		int perdidos();
		int empatados();

		void incPartidos();
		void incGanados();
		void incPerdidos();
		void incEmpatados();
		void limpiarPartidos();

		int play(genoma rival, bool sosA, int columns, int rows, int steps, bool firstA);
		void imprimirTablero();
		void imprimirGenoma();

	private:

		vector <int> genes_;
		int puntaje_;
		int partidos_;
		int ganados_;
		int perdidos_;
		int empatados_;

};
