CXX=g++
CXXFLAGS= -std=c++11 -g -Wall $(OPTIMIZATIONS)
OPTIMIZATIONS= -O2 -march=native

all: tp3 elizondo genetico grid

elizondo: elizondo.o Equipo.o Tablero.o Jugador.o Pelota.o Posicion.o Movimiento.o extras.o
	$(CXX) $(CXXFLAGS) $^ -o $@

tp3: tp3.o Equipo.o Tablero.o Jugador.o Pelota.o Posicion.o Movimiento.o extras.o
	$(CXX) $(CXXFLAGS) $^ -o $@

genetico:  Equipo.o Tablero.o Jugador.o Pelota.o Posicion.o Movimiento.o extras.o funGenetico.o
	$(CXX) $(CXXFLAGS) $^ -o $@

grid:  Equipo.o Tablero.o Jugador.o Pelota.o Posicion.o Movimiento.o extras.o GridSearch.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f tp3 *.o
	rm -f genetico *.o
	rm -f grid *.o
