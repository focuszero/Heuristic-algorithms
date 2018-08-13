////////////////////////////////////////////////////////////////////////////////
//Primer Cuatrimestre 2018. TRABAJO PRACTICO N°3: Darwin DT en el mundial 2018//
////////////////////////////////////////////////////////////////////////////////

#include "genoma.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR Y AUXILIARES DE LA CLASE ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

genoma::genoma()
{
	puntaje_ = 0;
	partidos_ = 0;
	ganados_ = 0;
	perdidos_ = 0;
	empatados_ = 0;
}

vector<int> genoma::genes()
{
	return genes_;
}

int genoma::puntaje()
{
	return puntaje_;
}

void genoma::agregarGen(int gen)
{
	genes_.push_back(gen);
}

void genoma::otorgarPuntaje(int puntaje)
{
	puntaje_ = puntaje;
}

void genoma::cargarGenes(vector<int> genes)
{
	genes_ = genes;
}

int genoma::partidos()
{
	return partidos_;
}

int genoma::ganados()
{
	return ganados_;
}

int genoma::perdidos()
{
	return perdidos_;
}

int genoma::empatados()
{
	return empatados_;
}

void genoma::incPartidos()
{
	partidos_++;
}

void genoma::incGanados()
{
	ganados_++;
	puntaje_ += 3;
	partidos_++;
}

void genoma::incPerdidos()
{
	perdidos_++;
	puntaje_ += 0;
	partidos_++;
}

void genoma::incEmpatados()
{
	empatados_++;
	puntaje_ += 1;
	partidos_++;
}

void genoma::limpiarPartidos()
{
	puntaje_ = 0;
	partidos_ = 0;
	ganados_ = 0;
	perdidos_ = 0;
	empatados_ = 0;
}

int genoma::play(genoma rival, bool sosA, int columns, int rows, int steps, bool firstA)
{
	cancha c = cancha(columns, rows);

	vector<int> arcoIzq1 = {c.columnaArcoIzq(), c.arcoIzquierdo()[0]};
	vector<int> arcoIzq2 = {c.columnaArcoIzq(), c.arcoIzquierdo()[1]};
	vector<int> arcoIzq3 = {c.columnaArcoIzq(), c.arcoIzquierdo()[2]};
	vector<int> arcoDer1 = {c.columnaArcoDer(), c.arcoDerecho()[0]};
	vector<int> arcoDer2 = {c.columnaArcoDer(), c.arcoDerecho()[1]};
	vector<int> arcoDer3 = {c.columnaArcoDer(), c.arcoDerecho()[2]};

	jugador jugador0 = jugador(abs(genes()[genes().size()-3]));
	jugador jugador1 = jugador(abs(genes()[genes().size()-2]));
	jugador jugador2 = jugador(abs(genes()[genes().size()-1]));
	jugador jugador3 = jugador(abs(rival.genes()[rival.genes().size()-3]));
	jugador jugador4 = jugador(abs(rival.genes()[rival.genes().size()-2]));
	jugador jugador5 = jugador(abs(rival.genes()[rival.genes().size()-1]));

	string lado;
	string ladoRival;
	if(sosA and firstA)
	{
		lado = "IZQUIERDA";
		ladoRival = "DERECHA";
	}
	else if(!sosA and !firstA)
	{
		lado = "IZQUIERDA";
		ladoRival = "DERECHA";
	}
	else
	{
		lado = "DERECHA";
		ladoRival = "IZQUIERDA";
	}

	if(lado == "IZQUIERDA") jugador0.adquierePelota();
	else jugador3.adquierePelota();

	vector<jugador> equipo = {jugador0, jugador1, jugador2};
	vector<jugador> equipoRival = {jugador3, jugador4, jugador5};

	player nosotros = player(c, steps, lado, equipo, equipoRival, genes());
	player ellos = player(c, steps, ladoRival, equipoRival, equipo, rival.genes());

	int misGoles = 0;
	int susGoles = 0;

	vector<vector<int> > ubicacionInicial = nosotros.calcularUbicacionInicialGoloso();
	vector<vector<int> > ubicacionInicialRival = ellos.calcularUbicacionInicialGoloso();

	for(unsigned int i = 0; i < equipo.size(); i++)
	{
		equipo[i].cambiarPosicion(ubicacionInicial[i][1], ubicacionInicial[i][0]);
		equipoRival[i].cambiarPosicion(ubicacionInicialRival[i][1], ubicacionInicialRival[i][0]);
	}

	nosotros.actualizarJuego(equipo, equipoRival);
	ellos.actualizarJuego(equipoRival, equipo);

	vector<int> posicionPelota = {(c.largo()/2) - 1, c.ancho()/2};
	vector<int> posicionPelotaFinal = posicionPelota;
	bool cambiarPelota = true;
	int direccion = 0;
	int fuerza = 0;

	for(int i = 0; i < steps; i++)
	{
		imprimirTablero();
		cambiarPelota = true;
		vector<vector<int> > proximoMov = nosotros.calcularProxMovGoloso();
		vector<vector<int> > proximoMovRival = ellos.calcularProxMovGoloso();
		for(unsigned int j = 0; j < equipo.size(); j++)
		{
			if(proximoMov[j][0] == 0)
			{
				equipo[j].actualizarPosicion(proximoMov[j][1]);
				if(equipo[j].tienePelota())
				{
					posicionPelota = equipo[j].posicion();
					posicionPelotaFinal = posicionPelota;
				}
			}

			if(proximoMovRival[j][0] == 0)
			{
				equipoRival[j].actualizarPosicion(proximoMovRival[j][1]);
				if(equipoRival[j].tienePelota())
				{
					posicionPelota = equipoRival[j].posicion();
					posicionPelotaFinal = posicionPelota;
				}
			}

			if(proximoMov[j][0] == 1)
			{
				posicionPelotaFinal = nosotros.futuraPosicionPelota(proximoMov[j][1], proximoMov[j][2]);
				posicionPelota = nosotros.futuraPosicionPelota(proximoMov[j][1], 1);
				nosotros.actualizarPosicionPelota(proximoMov[j][1], proximoMov[j][2]);
				ellos.actualizarPosicionPelota(proximoMov[j][1], proximoMov[j][2]);
				direccion = proximoMov[j][1];
				fuerza = proximoMov[j][2];
				cambiarPelota = false;
			}

			if(proximoMovRival[j][0] == 1)
			{
				posicionPelotaFinal = nosotros.futuraPosicionPelota(proximoMovRival[j][1], proximoMovRival[j][2]);
				posicionPelota = nosotros.futuraPosicionPelota(proximoMovRival[j][1], 1);
				nosotros.actualizarPosicionPelota(proximoMovRival[j][1], proximoMovRival[j][2]);
				ellos.actualizarPosicionPelota(proximoMovRival[j][1], proximoMovRival[j][2]);
				direccion = proximoMovRival[j][1];
				fuerza = proximoMovRival[j][2];
				cambiarPelota = false;
			}
		}

		if(posicionPelota != posicionPelotaFinal and cambiarPelota)
		{
			posicionPelota = nosotros.futuraPosicionPelota(direccion, 1);
			fuerza--;
			nosotros.actualizarPosicionPelota(direccion, fuerza);
			ellos.actualizarPosicionPelota(direccion, fuerza);
		}

		if( (lado == "IZQUIERDA" and (posicionPelota == arcoDer1 or posicionPelota == arcoDer2 or posicionPelota == arcoDer3)) or
		   	(lado == "DERECHA" and (posicionPelota == arcoIzq1 or posicionPelota == arcoIzq2 or posicionPelota == arcoIzq3)) )
		{
			misGoles++;
			i--;
			for(unsigned int j = 0; j < equipo.size(); j++)
			{
				equipo[j].cambiarPosicion(ubicacionInicial[j][1], ubicacionInicial[j][0]);
				equipoRival[j].cambiarPosicion(ubicacionInicialRival[j][1], ubicacionInicialRival[j][0]);
			}

			if(ladoRival == "IZQUIERDA")
			{
				equipoRival[0].cambiarPosicion(c.ancho()/2, (c.largo()/2) - 1);
				posicionPelota = {c.ancho()/2, (c.largo()/2) - 1};
				posicionPelotaFinal = posicionPelota;
				nosotros.nuevaPosicionPelota(posicionPelota);
				ellos.nuevaPosicionPelota(posicionPelota);
				equipoRival[0].adquierePelota();
			}
			if(ladoRival == "DERECHA")
			{
				equipoRival[0].cambiarPosicion(c.ancho()/2, (c.largo()/2));
				posicionPelota = {c.ancho()/2, (c.largo()/2)};
				posicionPelotaFinal = posicionPelota;
				nosotros.nuevaPosicionPelota(posicionPelota);
				ellos.nuevaPosicionPelota(posicionPelota);
				equipoRival[0].adquierePelota();
			}
			vector<int> posicionPelotaFinal = posicionPelota;
		}

		if( (ladoRival == "IZQUIERDA" and (posicionPelota == arcoDer1 or posicionPelota == arcoDer2 or posicionPelota == arcoDer3)) or
		   	(ladoRival == "DERECHA" and (posicionPelota == arcoIzq1 or posicionPelota == arcoIzq2 or posicionPelota == arcoIzq3)) )
		{
			susGoles++;
			i--;
			for(unsigned int j = 0; j < equipo.size(); j++)
			{
				equipo[j].cambiarPosicion(ubicacionInicial[j][1], ubicacionInicial[j][0]);
				equipoRival[j].cambiarPosicion(ubicacionInicialRival[j][1], ubicacionInicialRival[j][0]);
			}

			if(lado == "IZQUIERDA")
			{
				equipo[0].cambiarPosicion(c.ancho()/2, (c.largo()/2) - 1);
				posicionPelota = {c.ancho()/2, (c.largo()/2) - 1};
				posicionPelotaFinal = posicionPelota;
				nosotros.nuevaPosicionPelota(posicionPelota);
				ellos.nuevaPosicionPelota(posicionPelota);
				equipo[0].adquierePelota();
			}
			if(lado == "DERECHA")
			{
				equipo[0].cambiarPosicion(c.ancho()/2, (c.largo()/2));
				posicionPelota = {c.ancho()/2, (c.largo()/2)};
				posicionPelotaFinal = posicionPelota;
				nosotros.nuevaPosicionPelota(posicionPelota);
				ellos.nuevaPosicionPelota(posicionPelota);
				equipo[0].adquierePelota();
			}
			vector<int> posicionPelotaFinal = posicionPelota;
		}

		bool bGuarda = true;
		for(unsigned int k = 0; k < equipo.size(); k++)
		{
			for(unsigned int j = 0; j < equipoRival.size(); j++)
			{
				if(equipo[k].posicion() == equipoRival[j].posicion() and equipo[k].posicion() == posicionPelota)
				{
					bGuarda = false;
					srand(time(NULL));
					if(equipo[k].tienePelota())
					{
						int ganador = (rand() % 100)/100;
						float pQuitar = equipoRival[j].probaQuite()/(equipoRival[j].probaQuite() + (1 - equipo[k].probaQuite()));
						if(ganador <= pQuitar)
						{
							equipoRival[j].adquierePelota();
							equipo[k].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
						else
						{
							equipo[k].adquierePelota();
							equipoRival[j].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
					}
					else if(equipoRival[j].tienePelota())
					{
						int ganador = (rand() % 100)/100;
						float pQuitar = equipo[k].probaQuite()/(equipo[k].probaQuite() + (1 - equipoRival[j].probaQuite()));
						if(ganador <= pQuitar)
						{
							equipo[k].adquierePelota();
							equipoRival[j].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
						else
						{
							equipoRival[j].adquierePelota();
							equipo[k].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
					}
					else
					{
						int ganador = (rand() % 100)/100;
						float pGanar = equipo[k].probaQuite()/(equipo[k].probaQuite() + equipoRival[j].probaQuite());
						if(ganador <= pGanar)
						{
							equipo[k].adquierePelota();
							equipoRival[j].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
						else
						{
							equipoRival[j].adquierePelota();
							equipo[k].pierdePelota();
							posicionPelota == posicionPelotaFinal;
						}
					}
				}
			}

			if(posicionPelota == equipo[k].posicion() and bGuarda)
			{
				equipo[k].adquierePelota();
				posicionPelota == posicionPelotaFinal;
			}
			else if(posicionPelota != equipo[k].posicion())
				equipo[k].pierdePelota();

			if(posicionPelota == equipoRival[k].posicion() and bGuarda)
			{
				equipoRival[k].adquierePelota();
				posicionPelota == posicionPelotaFinal;
			}
			else if(posicionPelota != equipoRival[k].posicion())
				equipoRival[k].pierdePelota();
		}

		nosotros.actualizarJuego(equipo, equipoRival);
		ellos.actualizarJuego(equipoRival, equipo);
	}

	if(misGoles > susGoles)
	{
		return 3;
	}
	if(misGoles == susGoles)
	{
		return 1;
	}
	return 0;
}

void genoma::imprimirTablero()
{

}

void genoma::imprimirGenoma()
{
	cout << "Son " << genes_.size() - 3 << " genes -> ";
    for(unsigned int i = 0; i < genes_.size()-3; i++)
    {
        cout << genes_[i] << " ";
    }
	float proba;
	cout << "Y sus probabilidades de quite son -> ";
	proba = abs(genes_[genes_.size()-3]);
	cout << proba/100 << " ";
	proba = abs(genes_[genes_.size()-2]);
	cout << proba/100 << " ";
	proba = abs(genes_[genes_.size()-1]);
	cout << proba/100 << " ";
    cout << " Puntaje: " << puntaje_ << endl;
}
