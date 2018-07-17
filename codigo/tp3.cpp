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
                              Jugador(0, Posicion(1,1), 1),
                              Jugador(1, Posicion(2,2), 0.5),
                              Jugador(2, Posicion(3,3), 0.5)
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(6,4), 0.5),
                              Jugador(1, Posicion(7,2), 1),
                              Jugador(2, Posicion(8,3), 0.5)
        });

    const vector<double> gI(15, 0.99999);
    const vector<double> gD(15, 0.1343);

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
/*
 vector<Movimiento> mI1({
          Movimiento(ABAJO_DERECHA),
          Movimiento(QUIETO),
          Movimiento(QUIETO)
        });
        vector<Movimiento> quieto({
          Movimiento(QUIETO),
          Movimiento(QUIETO),
          Movimiento(QUIETO)
        });
        tablero.actualizar(
          mI1, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;
        tablero.actualizar(
          mI1, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;

    vector<Movimiento> mI2({
          Movimiento(DERECHA),
          Movimiento(QUIETO),
          Movimiento(QUIETO)
        });
        tablero.actualizar(
          mI2, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;

        tablero.actualizar(
          mI2, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;

        tablero.actualizar(
          mI2, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;

        vector<Movimiento> mI3({
          Movimiento(ARRIBA_DERECHA, 2),
          Movimiento(QUIETO),
          Movimiento(QUIETO)
        });
        tablero.actualizar(
          mI3, quieto
          //                 equipoI.turno(tablero),
            //               equipoD.turno(tablero)
                           );

        cout << tablero;
*/
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