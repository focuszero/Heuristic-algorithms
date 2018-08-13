all: goloso random busqueda genetic

################################################################################

goloso:
	g++ -std=c++11 -D_GLIBCXX_DEBUG -g -Wall playerGoloso.cpp player.cpp ../lib/cancha.cpp ../lib/jugador.cpp -o playerGoloso.out

random:
	g++ -std=c++11 -D_GLIBCXX_DEBUG -g -Wall playerRandom.cpp player.cpp ../lib/cancha.cpp ../lib/jugador.cpp -o playerRandom.out

busqueda:
	g++ -std=c++11 -W -D_GLIBCXX_DEBUG -g grasp/busquedaLocal.cpp -o grasp/busquedaLocal.out player.cpp ../lib/genoma.cpp ../lib/cancha.cpp ../lib/jugador.cpp

genetic:
	g++ -std=c++11 -D_GLIBCXX_DEBUG -g -Wall genetico/trainerGenetico.cpp genetico/genetico.cpp player.cpp ../lib/genoma.cpp ../lib/cancha.cpp ../lib/jugador.cpp -o genetico/trainerGenetico.out

trainer: 
	g++ -std=c++11 -D_GLIBCXX_DEBUG -g -Wall genetico/trainerMejores.cpp genetico/genetico.cpp player.cpp ../lib/genoma.cpp ../lib/cancha.cpp ../lib/jugador.cpp -o genetico/trainerMejores.out

################################################################################

clean:
	rm -fr *.out
	rm -fr grasp/*.out
	rm -fr genetico/*.out
	rm -fr ../TP3_mundial_src/*.pyc
	rm -fr ../TP3_mundial_src/log/
