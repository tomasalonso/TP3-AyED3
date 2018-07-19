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
                              Jugador(0, Posicion(1,1), 0.339975),
                              Jugador(1, Posicion(2,2), 0.0291968),
                              Jugador(2, Posicion(3,3), 0.568359)
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(6,4), 0.563661),
                              Jugador(1, Posicion(7,2), 0.219302),
                              Jugador(2, Posicion(8,3), 0.876167)
        });

    const vector<double> gI(
                      {0.663202, 0.14762, 0.334631, 0.720158, 0.891507,  0.429651,  0.952177,  0.999914,  0.68903 , 0.956027,  0.809002,  0.255012,  0.363912,  0.362843,  0.0419255,  0.0990008,  0.497539,  0.762558,  0.22842,  0.903021,  0.972504,  0.669737,  0.889001,  0.00694315,  0.803316,  0.272569 , 0.688622});
    const vector<double> gD({0.69081,  0.730877,  0.605143,  0.888566,  0.730022,  0.864344,  0.867599,  0.277615,  0.473535,  0.0216418,  0.765985,  0.386347,  0.176824,  0.729854,  0.49763,  0.371987,  0.0459012,  0.192031,  0.368118,  0.460835,  0.0705388,  0.501875,  0.506045,  0.533533,  0.0661474,  0.157776,  0.782478});

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
