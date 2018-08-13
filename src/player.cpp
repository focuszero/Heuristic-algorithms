////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include <stdlib.h>
#include <cmath>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR Y AUXILIARES DE LA CLASE ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
player::player()
{
	cancha_ = cancha();
	duracion_ = 100;
	lado_ = "DERECHA";
	jugador j = jugador();
	posicionPelota_ = {cancha_.largo()/2, cancha_.ancho()/2};
	equipo_ = {j, j, j};
	equipoRival_ = {j, j, j};
}

player::player(cancha c, int duracion, string lado, vector<jugador> nosotros, vector<jugador> ellos, vector<int> genoma)
{
	cancha_ = c;
	duracion_ = duracion;
	lado_ = lado;
	posicionPelota_ = {cancha_.largo()/2, cancha_.ancho()/2};
	equipo_ = nosotros;
	equipoRival_ = ellos;
	genoma_ = genoma;
}

void player::darUbicacion(vector<vector<int> > ubicaciones)
{
	for(unsigned int i = 0; i < ubicaciones.size(); i++)
	{
		cout << i << " " << ubicaciones[i][0] << " " << ubicaciones[i][1] << " ";
	}
	 cout << '\n';
}

void player::darJugada(vector<vector<int> > movimientos)
{//MOVER = 0 Y PASE = 1
	for(unsigned int i = 0; i < movimientos.size(); i++)
	{
		if(movimientos[i][0] == 0)
		{
			cout << i << " MOVIMIENTO " << movimientos[i][1] << " ";
		}
		else
		{
			cout << i << " PASE " << movimientos[i][1] << " " << movimientos[i][2] << " ";
		}
	}
	cout << '\n';
}

void player::obtenerGenoma()
{
	if(lado_ == "IZQUIERDA")
		genoma_ = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}; //Q: 0.72 0.16 0.07
	else
		genoma_ = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}; //Q: 0.37 0.95 0.17
}
	//Distancia a los contrarios
	//hice un pase
	//Distancia maxima a mi arco
	//Distancia a mi arco total
	//Distancia minima a mi arco
	//Puedo ir a quitar la pelota
	//Disputa por la pelota
	//Puedo interceptar la pelota a mi arco
	//Intercepte pelota
	//Puedo hacer GOL
	//Es GOL
	//Distancia a la pelota de un jugador
	//Distancia maxima al arco contrario
	//Distancia al arco contrario total
	//Distancia minima al arco contrario

void player::nuevaPosicionPelota(vector<int> posicionPelota)
{
	posicionPelota_ = posicionPelota;
}

void player::actualizarJuego(vector<jugador> nosotros, vector<jugador> ellos)
{
	equipo_ = nosotros;
	equipoRival_ = ellos;
}

bool player::jugadorFueraDeCancha(int direccion, int jugador)
{
	vector<int> arcoIzq1 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[0]};
	vector<int> arcoIzq2 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[1]};
	vector<int> arcoIzq3 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[2]};
	vector<int> arcoDer1 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[0]};
	vector<int> arcoDer2 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[1]};
	vector<int> arcoDer3 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[2]};

	vector<int> posJugadorVieja = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1]};

	if(direccion == 1)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] - 1, equipo_[jugador].posicion()[1] - 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 2)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] - 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 3)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] + 1, equipo_[jugador].posicion()[1] - 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 4)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] + 1, equipo_[jugador].posicion()[1]};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 5)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] + 1, equipo_[jugador].posicion()[1] + 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 6)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] + 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 7)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] - 1, equipo_[jugador].posicion()[1] + 1};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 8)
	{
		vector<int> posJugador = {equipo_[jugador].posicion()[0] - 1, equipo_[jugador].posicion()[1]};
		if(lado_ == "IZQUIERDA" and (posJugador == arcoDer1 or posJugador == arcoDer2 or posJugador == arcoDer3) and equipo_[jugador].tienePelota())
			return false;
		if(lado_ == "DERECHA" and (posJugador == arcoIzq1 or posJugador == arcoIzq2 or posJugador == arcoIzq3) and equipo_[jugador].tienePelota())
			return false;
		if(posJugador[0] < 0 or posJugador[0] > cancha_.largo()-1 or posJugador[1] < 0 or posJugador[1] > cancha_.ancho()-1)
			return true;
	}

	return false;
}

bool player::pelotaFueraDeCancha(int direccion, int fuerza, int jugador)
{
	vector<int> arcoIzq1 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[0]};
	vector<int> arcoIzq2 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[1]};
	vector<int> arcoIzq3 = {cancha_.columnaArcoIzq(), cancha_.arcoIzquierdo()[2]};
	vector<int> arcoDer1 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[0]};
	vector<int> arcoDer2 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[1]};
	vector<int> arcoDer3 = {cancha_.columnaArcoDer(), cancha_.arcoDerecho()[2]};

	if(direccion == 1)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] - fuerza*2, equipo_[jugador].posicion()[1] - fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] - (fuerza*2 - 1), equipo_[jugador].posicion()[1] - (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 2)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] - fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] - (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 3)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] + fuerza*2, equipo_[jugador].posicion()[1] - fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] + (fuerza*2 - 1), equipo_[jugador].posicion()[1] - (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 4)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] + fuerza*2, equipo_[jugador].posicion()[1]};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] + (fuerza*2 - 1), equipo_[jugador].posicion()[1]};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 5)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] + fuerza*2, equipo_[jugador].posicion()[1] + fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] + (fuerza*2 - 1), equipo_[jugador].posicion()[1] + (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 6)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] + fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0], equipo_[jugador].posicion()[1] + (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 7)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] - fuerza*2, equipo_[jugador].posicion()[1] + fuerza*2};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] - (fuerza*2 - 1), equipo_[jugador].posicion()[1] + (fuerza*2 - 1)};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	if(direccion == 8)
	{
		vector<int> posPelota = {equipo_[jugador].posicion()[0] - fuerza*2, equipo_[jugador].posicion()[1]};
		vector<int> posPelotaAnt = {equipo_[jugador].posicion()[0] - (fuerza*2 - 1), equipo_[jugador].posicion()[1]};
		if(lado_ == "IZQUIERDA" and (posPelota == arcoDer1 or posPelota == arcoDer2 or posPelota == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelota == arcoIzq1 or posPelota == arcoIzq2 or posPelota == arcoIzq3))
			return false;
		if(lado_ == "IZQUIERDA" and (posPelotaAnt == arcoDer1 or posPelotaAnt == arcoDer2 or posPelotaAnt == arcoDer3))
			return false;
		if(lado_ == "DERECHA" and (posPelotaAnt == arcoIzq1 or posPelotaAnt == arcoIzq2 or posPelotaAnt == arcoIzq3))
			return false;
		if(posPelota[0] < 0 or posPelota[0] > cancha_.largo()-1 or posPelota[1] < 0 or posPelota[1] > cancha_.ancho()-1)
			return true;
	}

	return false;
}

void player::actualizarPosicionPelota(int direccion, int fuerza)
{
	posicionPelota_ = futuraPosicionPelota(direccion, 1);
}

vector<int> player::futuraPosicionPelota(int direccion, int fuerza)
{
	vector<int> posicionPelotaFinal = posicionPelota_;

	if(direccion == 1)
	{
		posicionPelotaFinal[0] -= fuerza*2;
		posicionPelotaFinal[1] -= fuerza*2;
	}
	if(direccion == 2)
	{
		posicionPelotaFinal[1] -= fuerza*2;
	}
	if(direccion == 3)
	{
		posicionPelotaFinal[0] += fuerza*2;
		posicionPelotaFinal[1] -= fuerza*2;
	}
	if(direccion == 4)
	{
		posicionPelotaFinal[0] += fuerza*2;
	}
	if(direccion == 5)
	{
		posicionPelotaFinal[0] += fuerza*2;
		posicionPelotaFinal[1] += fuerza*2;
	}
	if(direccion == 6)
	{
		posicionPelotaFinal[1] += fuerza*2;
	}
	if(direccion == 7)
	{
		posicionPelotaFinal[0] -= fuerza*2;
		posicionPelotaFinal[1] += fuerza*2;
	}
	if(direccion == 8)
	{
		posicionPelotaFinal[0] -= fuerza*2;
	}

	return posicionPelotaFinal;
}

bool player::tenemosPelota()
{
	for(unsigned int i = 0; i < equipo_.size(); i++)
	{
		if( equipo_[i].posicion()[0] == posicionPelota_[0] and
			equipo_[i].posicion()[1] == posicionPelota_[1])
			return true;
	}

	return false;
}

bool player::tienenPelota()
{
	for(unsigned int i = 0; i < equipo_.size(); i++)
	{
		if( equipoRival_[i].posicion()[0] == posicionPelota_[0] and
			equipoRival_[i].posicion()[1] == posicionPelota_[1])
			return true;
	}

	return false;
}

/*chequeo si estoy alineado en altura con el arco rival, o sea, si puedo patearla al arco horizontalmente*/
bool player::horizontalArco(jugador goleador, int filaGol)
{
	bool metoGol = false;
	if((cancha_.ancho())/2 - 1 <= goleador.posicion()[1] and goleador.posicion()[1] <= (cancha_.ancho())/2 + 1)
	{
		metoGol = true;
		if((cancha_.ancho())/2 - 1 == goleador.posicion()[1])
		{
			filaGol = cancha_.ancho()/2 - 1;
		}
		else if((cancha_.ancho())/2 + 1 == goleador.posicion()[1])
		{
			filaGol = cancha_.ancho()/2 + 1;
		}
		else
		{
			filaGol = cancha_.ancho()/2;
		}
	}

	return metoGol;
}

/*chequeo si la distancia del jugador al arco en direccion horizontal es la misma a la distancia en
	 direccion vertical (o sea, si puedo patear diagonalmente al arco)*/
bool player::diagonalArco(jugador goleador, int filaGol)
{
	bool metoGol = false;
	if(lado_ == "DERECHA")
	{
		if( abs(goleador.posicion()[1]-cancha_.arcoIzquierdo()[0]) <= abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()) and
			abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()) <= abs(goleador.posicion()[1]-cancha_.arcoIzquierdo()[2]) )
		{
			metoGol = true;
			metoGol = metoGol and abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()) <= cancha_.ancho()/2;
			if(abs(goleador.posicion()[1]-cancha_.arcoIzquierdo()[0]) == abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()))
			{
				filaGol = cancha_.arcoIzquierdo()[0];
			}
			else if(abs(goleador.posicion()[1]-cancha_.arcoIzquierdo()[1]) == abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()))
			{
				filaGol = cancha_.arcoIzquierdo()[1];
			}
			else if(abs(goleador.posicion()[1]-cancha_.arcoIzquierdo()[2]) == abs(goleador.posicion()[0]-cancha_.columnaArcoIzq()))
			{
				filaGol = cancha_.arcoIzquierdo()[2];
			}
		}
	}
	else
	{
		if( abs(goleador.posicion()[1]-cancha_.arcoDerecho()[0]) <= abs(goleador.posicion()[0]-cancha_.columnaArcoDer()) and
			abs(goleador.posicion()[0]-cancha_.columnaArcoDer()) <= abs(goleador.posicion()[1]-cancha_.arcoDerecho()[2]))
		{
			metoGol = true;
			metoGol = metoGol and abs(goleador.posicion()[0]-cancha_.columnaArcoDer()) <= cancha_.ancho()/2;
			if(abs(goleador.posicion()[1]-cancha_.arcoDerecho()[0]) == abs(goleador.posicion()[0]-cancha_.columnaArcoDer()))
			{
				filaGol = cancha_.arcoDerecho()[0];
			}
			else if(abs(goleador.posicion()[1]-cancha_.arcoDerecho()[1]) == abs(goleador.posicion()[0]-cancha_.columnaArcoDer()))
			{
				filaGol = cancha_.arcoDerecho()[1];
			}
			else if(abs(goleador.posicion()[1]-cancha_.arcoDerecho()[2]) == abs(goleador.posicion()[0]-cancha_.columnaArcoDer()))
			{
				filaGol = cancha_.arcoDerecho()[2];
			}
		}
	}

	return metoGol;
}

bool player::interceptaTiroHorizontal(jugador goleador)
{
	bool meInterceptan = false;
	bool opuestoSeInterpone = false;
	if(lado_ == "DERECHA")
	{
		for(unsigned int i = 0; i < equipoRival_.size() and not meInterceptan; i++)
		{
			opuestoSeInterpone = equipoRival_[i].posicion()[0] < goleador.posicion()[0];
			if(opuestoSeInterpone)
			{
				for(int j = 0; j < goleador.posicion()[0] + 1; j++)
				{
					if( std::max(abs(equipoRival_[i].posicion()[0]-j),abs(equipoRival_[i].posicion()[1]-goleador.posicion()[1]))
						 < (goleador.posicion()[0] - j)/2 )
					{
						meInterceptan = true;
						break;
					}
				}
			}
		}
	}
	else
	{
		for(unsigned int i = 0; i < equipoRival_.size() and not meInterceptan; i++)
		{
			opuestoSeInterpone = equipoRival_[i].posicion()[0] > goleador.posicion()[0];
			if(opuestoSeInterpone)
			{
				for(int j = goleador.posicion()[0]; j < cancha_.largo(); j++)
				{
					if( std::max(abs(equipoRival_[i].posicion()[0]-j),abs(equipoRival_[i].posicion()[1]-goleador.posicion()[1]))
						 < (goleador.posicion()[0] - j)/2)
					{
						meInterceptan = true;
						break;
					}
				}
			}
		}
	}

	return meInterceptan;
}

bool player::interceptaTiroDiagonal(jugador goleador)
{
	bool meInterceptan = false;
	bool opuestoSeInterpone = false;
	if(lado_ == "DERECHA")
	{
		for(unsigned int i = 0; i < equipoRival_.size() and not meInterceptan; i++)
		{
			opuestoSeInterpone = equipoRival_[i].posicion()[0] < goleador.posicion()[0];
			if(opuestoSeInterpone)
			{
				if(goleador.posicion()[1] > cancha_.arcoIzquierdo()[1])
				{
					for(int j = 0; j < goleador.posicion()[0] + 1; j++)
					{
						if( std::max(abs(equipoRival_[i].posicion()[0] - (goleador.posicion()[0] - j)),
							    abs(equipoRival_[i].posicion()[1] - (goleador.posicion()[1] - j))) < j/2 )
						{
							meInterceptan = true;
							break;
						}
					}
				}
				else
				{
					for(int j = 0; j < goleador.posicion()[0] + 1; j++)
					{
						if( std::max(abs(equipoRival_[i].posicion()[0] - (goleador.posicion()[0] + j)),
								abs(equipoRival_[i].posicion()[1] - (goleador.posicion()[1] + j))) < j/2)
						{
							meInterceptan = true;
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		for(unsigned int i = 0; i < equipoRival_.size() and not meInterceptan; i++)
		{
			opuestoSeInterpone = equipoRival_[i].posicion()[0] > goleador.posicion()[0];
			if(opuestoSeInterpone)
			{
				if(goleador.posicion()[1] > cancha_.arcoIzquierdo()[1])
				{
					for(int j = 0; j < cancha_.largo() - goleador.posicion()[0]; j++)
					{
						if( std::max(abs(equipoRival_[i].posicion()[0] - (goleador.posicion()[0] + j)),
								abs(equipoRival_[i].posicion()[1] - (goleador.posicion()[1] - j))) < j/2)
						{
							meInterceptan = true;
							break;
						}
					}
				}
				else
				{
					for(int j = 0; j <  cancha_.largo() - goleador.posicion()[0]; j++)
					{
						if( std::max(abs(equipoRival_[i].posicion()[0] - (goleador.posicion()[0] + j)),
								abs(equipoRival_[i].posicion()[1] - (goleador.posicion()[1] + j))) < j/2)
						{
							meInterceptan = true;
							break;
						}
					}
				}
			}
		}
	}

	return meInterceptan;
}

vector<vector<vector<int> > > player::posiblesProxMovimientos(vector<vector<int> > actual, vector<vector<vector<int> > > proxMovimientos)
{
	if(actual.size() == equipo_.size())
	{
		bool mismoCasillero = false;

		for(unsigned int i = 0; i < actual.size(); i++)
		{
			for(unsigned int j = i+1; j < actual.size(); j++)
			{
				if(actual[i][0] == 0 and actual[j][0] == 0)
				{
					if( equipo_[i].futuraPosicion(actual[i][1])[0] == equipo_[j].futuraPosicion(actual[j][1])[0] and
						equipo_[i].futuraPosicion(actual[i][1])[1] == equipo_[j].futuraPosicion(actual[j][1])[1] )
						mismoCasillero = true;
				}
				if(actual[i][0] == 0 and actual[j][0] == 1)
				{
					if( equipo_[i].futuraPosicion(actual[i][1])[0] == equipo_[j].posicion()[0] and
						equipo_[i].futuraPosicion(actual[i][1])[1] == equipo_[j].posicion()[1] )
						mismoCasillero = true;
				}
				if(actual[i][0] == 1 and actual[j][0] == 0)
				{
					if( equipo_[i].posicion()[0] == equipo_[j].futuraPosicion(actual[j][1])[0] and
						equipo_[i].posicion()[1] == equipo_[j].futuraPosicion(actual[j][1])[1] )
						mismoCasillero = true;
				}
			}
		}

		if(!mismoCasillero)
			proxMovimientos.push_back(actual);
	}
	else
	{
		for(int i = 1; i < 9; i++)
		{
			if(!jugadorFueraDeCancha(i, actual.size()))
			{
				actual.push_back({0, i});
				proxMovimientos = posiblesProxMovimientos(actual, proxMovimientos);
				actual.pop_back();
			}
		}
		if(equipo_[actual.size()].tienePelota())
		{
			for(int j = 1; j < 4; j++)
			{
				for(int k = 1; k < cancha_.ancho()/2; k = k*2)
				{
					int l;
					if(lado_ == "DERECHA")
					{
						if(j == 1) l = 1;
						if(j == 2) l = 8;
						if(j == 3) l = 7;
					}
					else
					{
						if(j == 1) l = 3;
						if(j == 2) l = 4;
						if(j == 3) l = 5;
					}
					if(!pelotaFueraDeCancha(l, k, actual.size()))
					{
						actual.push_back({1, l, k});
						proxMovimientos = posiblesProxMovimientos(actual, proxMovimientos);
						actual.pop_back();
					}
				}
			}
		}
	}

	return proxMovimientos;
}

int player::puntuarEstado(vector<vector<int> > movimientos)
{
	player estadoActual = player(cancha_, duracion_, lado_, equipo_, equipoRival_, genoma_);
	estadoActual.nuevaPosicionPelota(posicionPelota_);
	vector<int> posicionPelotaFinal = estadoActual.posicionPelota_;

	for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
	{
		if(movimientos[i][0] == 0)
			(estadoActual.equipo_[i]).actualizarPosicion(movimientos[i][1]);
		else
		{
			posicionPelotaFinal = estadoActual.futuraPosicionPelota(movimientos[i][1], movimientos[i][2]);
			estadoActual.actualizarPosicionPelota(movimientos[i][1], movimientos[i][2]);
		}
	}

	vector<int> puntaje(15, 0);

	//Distancia minima al arco contrario
	float min;
	if(lado_ == "DERECHA")
	{
		min = (estadoActual.cancha_).largo();
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] < min)
				min = (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		min = 0;
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] > min)
				min = (estadoActual.equipo_[i]).posicion()[0];
		}
		min = (estadoActual.cancha_).largo() - min;
	}

	min = min/(estadoActual.cancha_).largo();
	puntaje[0] = min * genoma_[0];


	//Distancia al arco contrario total
	float total = 0;
	if(lado_ == "DERECHA")
	{
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			total += (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			total += (estadoActual.cancha_).largo() - (estadoActual.equipo_[i]).posicion()[0];
		}
	}

	total = total/((estadoActual.cancha_).largo()*3);
	puntaje[1] = total * genoma_[1];


	//Distancia maxima al arco contrario
	float max;
	if(lado_ == "DERECHA")
	{
		max = 0;
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] > max)
				max = (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		max = (estadoActual.cancha_).largo();
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] < max)
				max = (estadoActual.equipo_[i]).posicion()[0];
		}
		max = (estadoActual.cancha_).largo() - max;
	}

	max = max/(estadoActual.cancha_).largo();
	puntaje[2] = max * genoma_[2];


	//Distancia a la pelota de un jugador
	int dist_largo = abs(estadoActual.equipo_[0].posicion()[0] - estadoActual.posicionPelota_[0]);
	int dist_ancho = abs(estadoActual.equipo_[0].posicion()[1] - estadoActual.posicionPelota_[1]);
	float minDist = std::min(dist_largo, dist_ancho);
	for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
	{
		dist_largo = abs(estadoActual.equipo_[i].posicion()[0] - estadoActual.posicionPelota_[0]);
		dist_ancho = abs(estadoActual.equipo_[i].posicion()[1] - estadoActual.posicionPelota_[1]) ;
		if(std::min(dist_largo, dist_ancho ) < minDist)
			minDist = std::min(dist_largo, dist_ancho);
	}

	minDist = minDist/(estadoActual.cancha_).largo();
	puntaje[3] = minDist * genoma_[3];

	//Es GOL
	int gol = 0;
	vector<int> posPelota = {estadoActual.posicionPelota_[0], estadoActual.posicionPelota_[1]};
	vector<int> pos1Arco;
	vector<int> pos2Arco;
	vector<int> pos3Arco;
	if(lado_ == "DERECHA")
	{
		pos1Arco.push_back(estadoActual.cancha_.arcoIzquierdo()[0]);
		pos1Arco.push_back(estadoActual.cancha_.columnaArcoIzq());
		pos2Arco.push_back(estadoActual.cancha_.arcoIzquierdo()[1]);
		pos2Arco.push_back(estadoActual.cancha_.columnaArcoIzq());
		pos3Arco.push_back(estadoActual.cancha_.arcoIzquierdo()[2]);
		pos3Arco.push_back(estadoActual.cancha_.columnaArcoIzq());

	}
	else
	{
		pos1Arco.push_back(estadoActual.cancha_.arcoDerecho()[0]);
		pos1Arco.push_back(estadoActual.cancha_.columnaArcoDer());
		pos2Arco.push_back(estadoActual.cancha_.arcoDerecho()[1]);
		pos2Arco.push_back(estadoActual.cancha_.columnaArcoDer());
		pos3Arco.push_back(estadoActual.cancha_.arcoDerecho()[2]);
		pos3Arco.push_back(estadoActual.cancha_.columnaArcoDer());
	}

	if(posPelota == pos1Arco or posPelota == pos2Arco or posPelota == pos3Arco)
		gol = 1;

	//puntaje[4] = gol * genoma_[4];
	puntaje[4] = gol * 1000;

	//Puedo hacer GOL
	int hagoGol = 0;
	int filaGol = 0;
	for(unsigned int i = 0; i < estadoActual.equipo_.size(); i++)
	{
		if(estadoActual.equipo_[i].tienePelota())
		{
			if(horizontalArco(estadoActual.equipo_[i], filaGol))
			{
				hagoGol = 1;
				if(not interceptaTiroHorizontal(estadoActual.equipo_[i]))
					break;
				else
					hagoGol = 0;
			}
			else if(diagonalArco(estadoActual.equipo_[i], filaGol))
			{
				hagoGol = 1;
				if(not interceptaTiroDiagonal(estadoActual.equipo_[i]))
					break;
				else
					hagoGol = 0;
			}
		}
	}

	//puntaje[5] = hagoGol * genoma_[5];
	puntaje[5] = hagoGol * 1000;

	//Intercepte pelota
	int intercepte = 0;
	for(unsigned int i = 0; i < estadoActual.equipo_.size(); i++)
	{
		if(estadoActual.equipo_[i].posicion() == estadoActual.posicionPelota_)
		{
			intercepte = 1;
			break;
		}
	}

	puntaje[6] = intercepte * genoma_[6];

	//Puedo interceptar la pelota a mi arco
	int defiendo = 0;
	int filGol = 0;
	for(unsigned int i = 0; i < estadoActual.equipoRival_.size(); i++)
	{
		if(estadoActual.equipoRival_[i].tienePelota())
		{
			if(horizontalArco(estadoActual.equipoRival_[i], filGol))
			{
				defiendo = 1;
				if(interceptaTiroHorizontal(estadoActual.equipoRival_[i]))
					break;
				else
					defiendo = 0;
			}
			else if(diagonalArco(estadoActual.equipoRival_[i], filGol))
			{
				defiendo = 1;
				if(interceptaTiroDiagonal(estadoActual.equipoRival_[i]))
					break;
				else
					defiendo = 0;
			}
		}
	}

	puntaje[7] = defiendo * genoma_[7];

	//Disputa por la pelota
	int seDisputan = 0;
	for(unsigned int i = 0; i < estadoActual.equipo_.size() and seDisputan == 0; i++)
	{
		if(estadoActual.equipo_[i].posicion() == estadoActual.posicionPelota_)
		{
			for(unsigned int j = 0; j < estadoActual.equipoRival_.size(); j++)
			{
				if(estadoActual.equipoRival_[j].posicion() == estadoActual.posicionPelota_)
				{
					seDisputan = 1;
					break;
				}
			}
		}
	}

	puntaje[8] = seDisputan * genoma_[8];

	//Puedo ir a quitar la pelota
	int puedoQuitar = 0;
	for(unsigned int j = 0; j < estadoActual.equipoRival_.size(); j++)
	{
		if(estadoActual.equipoRival_[j].tienePelota())
		{
			for(unsigned int i = 0; i < estadoActual.equipo_.size(); i++)
			{
				if( abs(estadoActual.equipo_[i].posicion()[0]- estadoActual.equipoRival_[j].posicion()[0]) == 1 and
					abs(estadoActual.equipo_[i].posicion()[1]- estadoActual.equipoRival_[j].posicion()[1]) == 1)
				{
					puedoQuitar = 1;
					break;
				}
				else if(abs(estadoActual.equipo_[i].posicion()[0]- estadoActual.equipoRival_[j].posicion()[0]) == 1 and
						abs(estadoActual.equipo_[i].posicion()[1]- estadoActual.equipoRival_[j].posicion()[1]) == 0)
				{
					puedoQuitar = 1;
					break;
				}else if(abs(estadoActual.equipo_[i].posicion()[0]- estadoActual.equipoRival_[j].posicion()[0]) == 0 and
						 abs(estadoActual.equipo_[i].posicion()[1]- estadoActual.equipoRival_[j].posicion()[1]) == 1)
				{
					puedoQuitar = 1;
					break;
				}
			}
			if(puedoQuitar == 1)
			{
				break;
			}
		}
	}

	puntaje[9] = puedoQuitar * genoma_[9];

	//Distancia minima a mi arco
	float minArcoPropio;
	if(lado_ == "IZQUIERDA")
	{
		minArcoPropio = (estadoActual.cancha_).largo();
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] < minArcoPropio )
				minArcoPropio = (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		minArcoPropio = 0;
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] > minArcoPropio )
				minArcoPropio = (estadoActual.equipo_[i]).posicion()[0];
		}
		minArcoPropio = (estadoActual.cancha_).largo() - minArcoPropio;
	}

	minArcoPropio = minArcoPropio/(estadoActual.cancha_).largo();
	puntaje[10] = minArcoPropio * genoma_[10];

	//Distancia a mi arco total
	float totalArcoPropio = 0;
	if(lado_ == "IZQUIERDA")
	{
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			totalArcoPropio += (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			totalArcoPropio += (estadoActual.cancha_).largo() - (estadoActual.equipo_[i]).posicion()[0];
		}
	}

	totalArcoPropio = totalArcoPropio/(estadoActual.cancha_).largo();
	puntaje[11] = totalArcoPropio * genoma_[11];

	//Distancia maxima a mi arco
	float maxArcoPropio;
	if(lado_ == "IZQUIERDA")
	{
		maxArcoPropio = 0;
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] > maxArcoPropio )
				maxArcoPropio = (estadoActual.equipo_[i]).posicion()[0] + 1;
		}
	}
	else
	{
		maxArcoPropio = (estadoActual.cancha_).largo();
		for(unsigned int i = 0; i < (estadoActual.equipo_).size(); i++)
		{
			if((estadoActual.equipo_[i]).posicion()[0] < maxArcoPropio )
				maxArcoPropio = (estadoActual.equipo_[i]).posicion()[0];
		}
		maxArcoPropio = (estadoActual.cancha_).largo() - maxArcoPropio;
	}

	maxArcoPropio = maxArcoPropio/(estadoActual.cancha_).largo();
	puntaje[12] = maxArcoPropio * genoma_[12];

	//hice un pase
	int hicePase = 0;
	for(unsigned int i = 0; i < estadoActual.equipo_.size(); i++)
	{
		if( abs(estadoActual.equipo_[i].posicion()[0] - estadoActual.posicionPelota_[0]) == 2 and
			abs(estadoActual.equipo_[i].posicion()[1] - estadoActual.posicionPelota_[1]) == 2)
		{
			hicePase = 1;
			break;
		}
		else if(abs(estadoActual.equipo_[i].posicion()[0] - estadoActual.posicionPelota_[0]) == 2 and
				abs(estadoActual.equipo_[i].posicion()[1] - estadoActual.posicionPelota_[1]) == 0)
		{
			hicePase = 1;
			break;
		}
		else if(abs(estadoActual.equipo_[i].posicion()[0] - estadoActual.posicionPelota_[0]) == 0 and
				abs(estadoActual.equipo_[i].posicion()[1] - estadoActual.posicionPelota_[1]) == 2)
		{
			hicePase = 1;
			break;
		}
	}

	puntaje[13] = hicePase * genoma_[13];

	//Distancia a los contrarios
	float distContrarios = estadoActual.cancha_.largo();
	for(unsigned int i = 0; i < estadoActual.equipo_.size(); i++)
	{
		for(unsigned int j = 0; j < estadoActual.equipoRival_.size(); j++)
		{
			if( std::max(abs(estadoActual.equipo_[i].posicion()[0]-estadoActual.equipoRival_[j].posicion()[0]),
					abs(estadoActual.equipo_[i].posicion()[1]-estadoActual.equipoRival_[j].posicion()[1])) < distContrarios)
			{
				distContrarios = std::max(abs(estadoActual.equipo_[i].posicion()[0]-estadoActual.equipoRival_[j].posicion()[0]),
									 abs(estadoActual.equipo_[i].posicion()[1]-estadoActual.equipoRival_[j].posicion()[1]));
			}
		}
	}

	distContrarios = distContrarios/(estadoActual.cancha_).largo();
	puntaje[14] = distContrarios * genoma_[14];

	float sumaPuntaje = 0;
	for(unsigned int i = 0; i < puntaje.size(); i++)
	{
		sumaPuntaje = sumaPuntaje + puntaje[i];
	}
	return sumaPuntaje;
}

////////////////////////////////////////////////////////////////////////////////
// PLAYER GOLOSO ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

vector<vector<int> > player::calcularUbicacionInicialGoloso()
{
	vector<vector<int> > ubicaciones;

	if(lado_ == "DERECHA")
		ubicaciones =	{	{cancha_.ancho()/2, (cancha_.largo()/8)*5 + 1},
							{(cancha_.ancho()/4), (cancha_.largo()/4)*3 + 1},
							{(cancha_.ancho()/4)*3, (cancha_.largo()/4)*3 + 1}
						};
	else
		ubicaciones =	{	{cancha_.ancho()/2, (cancha_.largo()/2) - 1},
							{(cancha_.ancho()/4), cancha_.largo()/4},
							{(cancha_.ancho()/4)*3, cancha_.largo()/4}
						};

	return ubicaciones;
}

vector<vector<int> > player::calcularProxMovGoloso()
{
	srand(time(NULL));
	vector<vector<vector<int> > > proxMovimientos;
	vector<vector<int> > actual;
	proxMovimientos = posiblesProxMovimientos(actual, proxMovimientos);
	int maxEstado = -999999999;
	vector<vector<int> > maxJugada;

	for(unsigned int i = 0; i < proxMovimientos.size(); i++)
	{
		int puntaje = puntuarEstado(proxMovimientos[i]);

		if(puntaje > maxEstado)
		{
			maxEstado = puntaje;
			maxJugada = proxMovimientos[i];
		}

		if(puntaje == maxEstado)
		{
			int n = rand() % 2;
			if(n == 0)
			{
				maxEstado = puntaje;
				maxJugada = proxMovimientos[i];
			}
		}
	}

	return maxJugada;
}

////////////////////////////////////////////////////////////////////////////////
// PLAYER RANDOM ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

vector<vector<int> > player::calcularUbicacionInicialRandom()
{
	srand(time(NULL));
	vector<vector<int> > ubicaciones;

	for(unsigned int i = 0; i < equipo_.size(); i++)
	{
		int n = rand() % cancha_.largo()/2;
		int m = rand() % cancha_.ancho();
		if(lado_ == "DERECHA")
		{
			n =+ cancha_.largo()/2;
		}
		vector<int> ubicacion = {m, n};
		ubicaciones.push_back(ubicacion);
	}

	return ubicaciones;
}

vector<vector<int> > player::calcularProxMovRandom()
{
	srand(time(NULL));
	vector<vector<int> > movimientos;

	for(unsigned int i = 0; i < equipo_.size(); i++)
	{
		int tipoMov = 0;
		if(equipo_[i].tienePelota()) tipoMov = rand() % 2;

		vector<int> movimiento;
		if(tipoMov == 0)
		{
			int direccion = rand() % 9;
			while(jugadorFueraDeCancha(direccion, i))
			{
				direccion = rand() % 9;
			}
			movimiento = {tipoMov, direccion};
		}
		else
		{
			int direccion = rand() % 8 + 1;
			int fuerza = (rand() % (cancha_.ancho() + 1)/2) + 1;
			while(pelotaFueraDeCancha(direccion, fuerza, i))
			{
				direccion = rand() % 8 + 1;
				fuerza = (rand() % (cancha_.ancho() + 1)/2) + 1;
			}
			movimiento = {tipoMov, direccion, fuerza};
		}
		movimientos.push_back(movimiento);
	}

	return movimientos;
}
