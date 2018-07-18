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
    const unsigned int total = 100;

    const vector<Jugador> jI({
                              Jugador(0, Posicion(1,1), 0.152869),
                              Jugador(1, Posicion(2,2), 0.67807),
                              Jugador(2, Posicion(3,3), 0.137978)
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(6,4), 0.288556),
                              Jugador(1, Posicion(7,2), 0.429239),
                              Jugador(2, Posicion(8,3), 0.595944)
        });

    const vector<double> gD(
                      {0.902997, 0.567549, 0.919372, 0.647458, 0.11399, 0.000219284, 0.459814, 0.933624, 0.0704338, 0.18382, 0.231627, 0.363771, 0.352568, 0.118043, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.152869, 0.67807, 0.137978, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 });
    const vector<double> gI({0.355141, 0.626732, 0.827152, 0.860142, 0.69954, 0.48047, 0.764234, 0.101884, 0.268695, 0.743567, 0.817875, 0.372644, 0.928222, 0.196441, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.288556, 0.429239, 0.595944, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 });

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
