CXX=g++
CXXFLAGS= -std=c++11 -g -Wall $(OPTIMIZATIONS)
OPTIMIZATIONS= -O2 -march=native

all: tp3

tp3: tp3.o Equipo.o Juego.o Jugador.o Movimiento.o Pelota.o Posicion.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f tp3 *.o