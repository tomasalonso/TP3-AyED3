#include <iostream>
#include <sstream>
#include <string>

#include "Equipo.hpp"
#include "Tablero.hpp"

using namespace std;


int main() {
    const unsigned int m = 5;
    const unsigned int n = 10;
    const unsigned int total = 10;

    const vector<Jugador> jI({
                              Jugador(0, Posicion(1,1), 0.5),
                              Jugador(1, Posicion(2,2), 0.5),
                              Jugador(2, Posicion(3,3), 0.5)
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(6,1), 0.5),
                              Jugador(1, Posicion(7,2), 0.5),
                              Jugador(2, Posicion(8,3), 0.5)
        });

    const vector<int> gI({5,5});
    const vector<int> gD({5,5});

    Equipo equipoI(gI, false);
    Equipo equipoD(gD, true);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero, equipoI.genJugadas1()),
                           equipoD.turno(tablero, equipoD.genJugadas1())
                           );
        tablero.imprimirEstado(true);
    }
}
