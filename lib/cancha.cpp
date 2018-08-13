////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "cancha.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR Y AUXILIARES DE LA CLASE ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
cancha::cancha()
{
	ancho_ = 3;
	largo_ = 6;
	arcoDer_ = {0, 1, 2};
	arcoIzq_ = {0, 1, 2};
}

cancha::cancha(int n, int m)
{
	ancho_ = m;
	largo_ = n;
	arcoDer_ = {m/2 - 1, m/2, m/2 + 1};
	arcoIzq_ = {m/2 - 1, m/2, m/2 + 1};
}

int cancha::ancho()
{
	return ancho_;
}

int cancha::largo()
{
	return largo_;
}

vector<int> cancha::arcoDerecho()
{
	return arcoDer_;
}

vector<int> cancha::arcoIzquierdo()
{
	return arcoIzq_;
}

int cancha::columnaArcoDer()
{
	return largo_;
}

int cancha::columnaArcoIzq()
{
	return -1;
}
