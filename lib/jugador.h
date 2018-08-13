////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class jugador
{

	public:

		//----------------------Constructor-y-Auxiliares----------------------//
		jugador();

		jugador(float);

		float probaQuite();

		vector<int> posicion();

		bool tienePelota();

		void cambiarPosicion(int, int);

		void actualizarPosicion(int);

		vector<int> futuraPosicion(int);

		void adquierePelota();

		void pierdePelota();

	private:

		float probaQuite_;
		vector<int> posicion_;
		bool tienePelota_;

};
