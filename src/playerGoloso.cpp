////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "player.h"

using namespace std;

int main(int argc, char const *argv[])
{
	int n, m, s;
	string lado;

	cin >> n >> m >> s;
	cin >> lado;

	vector<float> probaQuiteJugadores(6);

	for(int i = 0; i < 6; i++)
	{
		int jugador;
		cin >> jugador;
		cin >> probaQuiteJugadores[i];
	}

	cancha c = cancha(n, m);
	vector<jugador> jugadores(6);
	jugadores[0] = jugador(probaQuiteJugadores[0]);
	jugadores[1] = jugador(probaQuiteJugadores[1]);
	jugadores[2] = jugador(probaQuiteJugadores[2]);
	jugadores[3] = jugador(probaQuiteJugadores[3]);
	jugadores[4] = jugador(probaQuiteJugadores[4]);
	jugadores[5] = jugador(probaQuiteJugadores[5]);

	vector<jugador> equipo = {jugadores[0], jugadores[1], jugadores[2]};
	vector<jugador> equipoRival = {jugadores[3], jugadores[4], jugadores[5]};

	vector<int> genoma;
	player goloso = player(c, s, lado, equipo, equipoRival, genoma);
	goloso.obtenerGenoma();

	vector<vector<int> > ubicacionInicial = goloso.calcularUbicacionInicialGoloso();
	goloso.darUbicacion(ubicacionInicial);

	for(int j = 0; j < s; j++)
	{
		bool pelotaSola = true;
		vector<int> posicionPelota;

		for(int i = 0; i < 6; i++)
		{
			string mensaje;
			cin >> mensaje;

			int n, m;
			cin >> m >> n;
			jugadores[i].cambiarPosicion(n, m);

			string tienePelota;
			cin >> tienePelota;

			if(tienePelota == "CON_PELOTA")
			{
				jugadores[i].adquierePelota();
				pelotaSola = false;
				posicionPelota = {n, m};
			}
			else
				jugadores[i].pierdePelota();

		}

		if(pelotaSola == true)
		{
			int n, m;
			int dir, potencia;
			cin >> m >> n;
			posicionPelota = {n, m};
			cin >> dir >> potencia;
		}

		goloso.nuevaPosicionPelota(posicionPelota);

		vector<jugador> equipo = {jugadores[0], jugadores[1], jugadores[2]};
		vector<jugador> equipoRival = {jugadores[3], jugadores[4], jugadores[5]};
		goloso.actualizarJuego(equipo, equipoRival);

		vector<vector<int> > proximoMov = goloso.calcularProxMovGoloso();
		goloso.darJugada(proximoMov);
	}

	string mensaje;
	cin >> mensaje;

	return 0;
}
