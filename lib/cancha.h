////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class cancha
{

	public:

		//----------------------Constructor-y-Auxiliares----------------------//
		cancha();

		cancha(int, int);

		int ancho();

		int largo();

		vector<int> arcoDerecho();

		vector<int> arcoIzquierdo();

		int columnaArcoDer();

		int columnaArcoIzq();


	private:

		vector<int> arcoDer_;
		vector<int> arcoIzq_;
		int ancho_;
		int largo_;
};
