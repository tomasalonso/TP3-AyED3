#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Equipo.hpp"
#include "Tablero.hpp"
#include "extras.hpp"


int main() {
    const int m = 5;
    const int n = 10;
    const unsigned int total = 20;

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

    const vector<double> gI(15, 0.7);
    const vector<double> gD(15, 0.7);

    Equipo equipoI(gI, false);
    Equipo equipoD(gD, true);

    Tablero tablero(m, n, total, jI, jD);

    /*
    Jugador elJugador(0, Posicion(5,0), 0.5);
    vector<Movimiento> movs;
    tablero.jugadasValidasJug(elJugador, movs);

    cout << movs << endl;
    */
    cout << tablero << endl;
    while (!tablero.terminado()) { 
        //cout << equipoI.turno(tablero) << endl;
        //cout << equipoD.turno(tablero) << endl;
      
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );

        cout << tablero;

        std::string line;
        std::getline(std::cin, line);
    }

    return 0;
}