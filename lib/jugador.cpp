////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "jugador.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR Y AUXILIARES DE LA CLASE ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
jugador::jugador()
{
	probaQuite_ = 0.5;
	posicion_ = {0, 0};
	tienePelota_ = false;
}

jugador::jugador(float probaQuite)
{
	probaQuite_ = probaQuite;
	posicion_ = {0, 0};
	tienePelota_ = false;
}

float jugador::probaQuite()
{
	return probaQuite_;
}

vector<int> jugador::posicion()
{
	return posicion_;
}

bool jugador::tienePelota()
{
	return tienePelota_;
}

void jugador::cambiarPosicion(int n, int m)
{
	posicion_ = {n, m};
}

void jugador::actualizarPosicion(int direccion)
{
	if(direccion == 1)
	{
		posicion_[0] -= 1;
		posicion_[1] -= 1;
	}
	if(direccion == 2)
	{
		posicion_[1] -= 1;
	}
	if(direccion == 3)
	{
		posicion_[0] += 1;
		posicion_[1] -= 1;
	}
	if(direccion == 4)
	{
		posicion_[0] += 1;
	}
	if(direccion == 5)
	{
		posicion_[0] += 1;
		posicion_[1] += 1;
	}
	if(direccion == 6)
	{
		posicion_[1] += 1;
	}
	if(direccion == 7)
	{
		posicion_[0] -= 1;
		posicion_[1] += 1;
	}
	if(direccion == 8)
	{
		posicion_[0] -= 1;
	}
}

vector<int> jugador::futuraPosicion(int direccion)
{
	if(direccion == 1)
	{
		return {posicion_[0] - 1, posicion_[1] - 1};
	}
	if(direccion == 2)
	{
		return {posicion_[0], posicion_[1] - 1};
	}
	if(direccion == 3)
	{
		return {posicion_[0] + 1, posicion_[1] - 1};
	}
	if(direccion == 4)
	{
		return {posicion_[0] + 1, posicion_[1]};
	}
	if(direccion == 5)
	{
		return {posicion_[0] + 1, posicion_[1] + 1};
	}
	if(direccion == 6)
	{
		return {posicion_[0], posicion_[1] + 1};
	}
	if(direccion == 7)
	{
		return {posicion_[0] - 1, posicion_[1] + 1};
	}
	if(direccion == 8)
	{
		return {posicion_[0] - 1, posicion_[1]};
	}

	return {posicion_[0], posicion_[1]};
}

void jugador::adquierePelota()
{
	tienePelota_ = true;
}

void jugador::pierdePelota()
{
	tienePelota_ = false;
}
