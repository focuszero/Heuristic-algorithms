////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "../lib/cancha.h"
#include "../lib/jugador.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class player
{

	public:

		//----------------------Constructor-y-Auxiliares----------------------//
		player();

		player(cancha c, int duracion, string lado, vector<jugador> nosotros, vector<jugador> ellos, vector<int> genoma);

		void darUbicacion(vector<vector<int> > ubicaciones);
		void darJugada(vector<vector<int> > movimientos);
		void obtenerGenoma();
		void nuevaPosicionPelota(vector<int> posicionPelota);
		void actualizarJuego(vector<jugador> nosotros, vector<jugador> ellos);
		void actualizarPosicionPelota(int direccion, int fuerza);
		vector<int> futuraPosicionPelota(int direccion, int fuerza);

		vector<vector<int> > calcularUbicacionInicialGoloso();
		vector<vector<int> > calcularProxMovGoloso();

		vector<vector<int> > calcularUbicacionInicialRandom();
		vector<vector<int> > calcularProxMovRandom();

	private:

		cancha cancha_;
		int duracion_;
		string lado_;
		vector<int> posicionPelota_;
		vector<jugador> equipo_;
		vector<jugador> equipoRival_;
		vector<int> genoma_;

		bool jugadorFueraDeCancha(int direccion, int jugador);
		bool pelotaFueraDeCancha(int direccion, int fuerza, int jugador);
		bool tenemosPelota();
		bool tienenPelota();
		bool horizontalArco(jugador goleador, int filaGol);
		bool diagonalArco(jugador goleador, int filaGol);
		bool interceptaTiroHorizontal(jugador goleador);
		bool interceptaTiroDiagonal(jugador goleador);
		vector<vector<vector<int> > > posiblesProxMovimientos(vector<vector<int> > actual, vector<vector<vector<int> > > proxMovimientos);
		int puntuarEstado(vector<vector<int> > movimientos);

};
