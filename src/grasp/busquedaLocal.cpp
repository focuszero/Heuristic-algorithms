#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <chrono>


#include "../../lib/genoma.h"
//#include "../genetico/genetico.h"

#include <algorithm>


using namespace std;



//string ls = GetStdoutFromCommand("ls -la");        // ejemplo de función para obtener el stdout de un commando de terminal
//
//cout << "LS: " << ls << endl;


// string GetStdoutFromCommand(string cmd) {

//     string data;
//     FILE * stream;
//     const int max_buffer = 256;
//     char buffer[max_buffer];
//     // cmd.append(" 2>&1");

//     stream = popen(cmd.c_str(), "r");
//     if (stream) {
//         while (!feof(stream))
//             if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
//         pclose(stream);
//     }
//     return data;
// }


int main() {

    bool mejoro = false;

    while(!mejoro){

        mejoro = false;
        
        int cantidad_mejoras = 200;                          // 100 mejoras

        vector<int> genomaRand (18,0);

        srand (time(NULL));                                 /* initialize random seed: */

                                                            // lleno un genoma random
        for (unsigned int i = 0; i < genomaRand.size(); ++i) {

            genomaRand[i] = (rand() % 101);        // Suponiendo que las variables del genoma estan entre -100 y 100

        }

        genoma gen = genoma();

        gen.cargarGenes(genomaRand);

        // genoma gen2 = generarGenomaRandom();

        // vector<int> genes = gen2.genes();



        auto startGrasp = chrono::steady_clock::now();

        float fitnessActual = 0;

        do
        {

            cantidad_mejoras--;
            vector<vector<int> > vecindario (genomaRand.size()*2, genomaRand);                    // Genero el vecindario
                                                                                                // Los vecinos van a ser los genomas que son
                                                                                            // iguales al actual excepto por 1 variable +- 5

            for (unsigned int j = 0; j < genomaRand.size(); ++j) {
                if (vecindario[j][j] < 60)
                    vecindario[j][j] = vecindario[j][j] + 40;
                else
                    vecindario[j][j] = vecindario[j][j] - 50;

                if (vecindario[j + genomaRand.size()][j] > -60)
                    vecindario[j + genomaRand.size()][j] = vecindario[j + genomaRand.size()][j] - 40;
                else
                    vecindario[j + genomaRand.size()][j] = vecindario[j + genomaRand.size()][j] + 50;
            }

            std::random_shuffle ( vecindario.begin(), vecindario.end() );

            vector<int> fitness (genomaRand.size()*2, 0);

            std::cout << "arranca " << endl;

            int ancho = 10;
            int alto = 5;
            int steps = 35;
            int resultadoMejor = 0;

            for (unsigned int l = 0; l < fitness.size(); ++l) {               // Aca juego el partido, deberiamos jugar 5 o 10 partidos
                int resultado = 0;
                int resultadoRival = 0;

                genoma rival;
                rival.cargarGenes(vecindario[l]);

                std::cout << "Jugando Partidos contra vecino " << l << endl;

                auto startPartidos = chrono::steady_clock::now();

                for(size_t i = 0; i < 5; i++)
                {
                    bool azul = rand() % 1;
                    bool primeroAzul = rand() % 1;
                    int puntos = gen.play(rival, azul, ancho, alto, steps, primeroAzul); // comando a ejecutar algo del estilo "python2 Elizondo.py --team_B ./playerRandom.out random_B --quites_B 0.5 0.5 0.5 --columns 10 --rows 5 --steps 50 --first A"

                        if (puntos == 0) {       //
                            resultadoRival += 3;

                        } else if (puntos == 1) {
                            resultadoRival++;
                            resultado++;

                        }else if(puntos == 3) {
                            resultado += 3;
                        }
                }

                auto endPartidos = chrono::steady_clock::now();

                std::cout << "Resultado " << resultadoRival << endl;

                auto diffPartidos = endPartidos - startPartidos;

                cout << chrono::duration <double, milli> (diffPartidos).count() << endl;

                fitness[l] = resultadoRival;                     // pero con el genoma actual

                if (resultadoRival > 9){
                    break;    
                }
            }

            // Hago jugar todos los partidos para decidir el fitness (cada partido se juega varias veces empezando con la pelota y sin)
            // Comparo los Fitness resultantes para quedarme con el que mejor resultado obtenga y ese es mi nuevo Genoma
            int maxFitness = 0;
            int index = 0;
            for (unsigned int k = 0; k < fitness.size(); ++k) {                  // Busco el mejor fitness del Vecindario
                if (fitness[k] > maxFitness) {
                    maxFitness = fitness[k];
                    index = k;
                };
            }

            mejoro = false;
            if (maxFitness > 9){                            // Me fijo si el Fitness del vecindario el mejor al mio

                std::cout << "Yo soy: " << endl;
                for (const auto& i: genomaRand)                 // Imprimo el Genoma actual
                    std::cout << i << ' ';

                std::cout << "El mejor fue: " << index << endl;
                for (const auto& i: vecindario[index])          // Imprimo el mejor Genoma
                    std::cout << i << ' ';

                fitnessActual = maxFitness;
                gen.cargarGenes(vecindario[index]);
                genomaRand = vecindario[index];
                //genoma = vecindario[index];
                mejoro = true;

                std::cout << "Generación " << cantidad_mejoras;

                cout << endl;
            }
        }

        while(mejoro and cantidad_mejoras > 0);                     // Me fijo que no sea el máximo local y que no paso la cant máxima de mejoras

        auto endGrasp = chrono::steady_clock::now();
        auto diffGrasp = endGrasp - startGrasp;

        cout << chrono::duration <double, milli> (diffGrasp).count() << endl;

        // for (const auto& i: vecindario[index])         // Imprimo el Genoma final
        //     std::cout << i << ' ';
    }
    return 0;
}
