#include "Equipo.hpp"

#include <cassert>


Equipo::Equipo(Genoma genoma, bool enDerecha) : _genoma(genoma), _enDerecha(enDerecha) {}

// const Jugador& Equipo::jugador(size_t i) const {
//     assert(i < 6);
//     if(i/3) {
//         return _tablero.verJugadores(false)[i%3];
//     }

//     return _tablero.verJugadores(true)[i%3];
// }

bool Equipo::enDerecha() {
    return _enDerecha;
}

// void Equipo::reiniciar(bool metiGol) {
// }

// actualiza tablero, prueba jugadas y devuelve la mejor
vector<Movimiento> Equipo::turno(Tablero &t, const vector<vector<Movimiento>> &jugadas) {
    vector<Movimiento> mejorJugada;
    // generamos de manera todos los movimientos
    // (asumimos que el oponente se queda quieto)
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente
    int puntajeMejor = -1;
    int puntajeActual;
    for (auto &j : jugadas) {  // Devuelve todas válidas
        // t.mover(j);
        // puntajeActual = t.evaluar();
        // if(puntajeActual > puntajeMejor) {
        //     puntajeMejor = puntajeActual;
        //     mejorJugada = j;
        // }
    }

    return mejorJugada;
}

vector<vector<Movimiento>> Equipo::genJugadas1() {  // Prueba TODAS las jugadas

    vector<vector<Movimiento>> jugadas;

    // int filas = _tablero.M();
    // int totalDirs = 9;

    // // Por cada jugada jugador 1
    // for (int i = 0; i < totalDirs; ++i) {

    //     // Por cada jugada jugador 2
    //     for (int j = 0; j < totalDirs; ++j) {

    //         // Por cada jugada jugador 3
    //         for (int k = 0; k < totalDirs; ++k) {

    //             // Todos se mueven
    //             vector<Movimiento> jugada = { Movimiento((Direccion)i),
    //                                           Movimiento((Direccion)j),
    //                                           Movimiento((Direccion)k)  };

    //             if(esJugadaValida(jugada)) {
    //                 jugadas.push_back(jugada);
    //             }

    //             // Si alguno tiene la pelota, considero los posibles pases
    //             if(_tablero.pelotaEnPosesion()) {

    //                 int idJugadorPelota = (int)(_tablero.jugadorPelota()).id();
    //                 if(idJugadorPelota < 4) {   // es de mi equipo

    //                     // Por cada posible direccion
    //                     for (int dir = 1; dir < 9; ++dir) {

    //                         // Pongo esto para no probar más intensidades de las necesarias en una misma dirección
    //                         bool intensidadTope = false;
    //                         // Por cada posible intensidad
    //                         for (int inten = 0; inten < filas/2 && !intensidadTope ; ++inten) {

    //                             jugada[idJugadorPelota] = Movimiento((Direccion)dir, inten);
    //                             if(esJugadaValida(jugada)) {
    //                                 jugadas.push_back(jugada);
    //                             } else {
    //                                 intensidadTope = true;
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }

    //     }
    // }
    return jugadas;
}

// void Equipo::imprimirMovs (vector<Movimiento>& movs) {
//     for (int i = 0; i < (int)movs.size(); i++) {
//         if (movs[i].moverse) {
//             printf("%d %s %d\n", i, "MOVIMIENTO", (int)movs[i].dir);
//         } else {
//             printf("%d %s %d %d\n", i, "PASE", (int)movs[i].dir, movs[i].intensidad);
//         }
//     }
// }

// vector<tuple<int, int, int, string> > leerEstadoArbitro(iostream& in) {
//     vector<tuple<int, int, int, string> > estados (6);
//     bool leerPelota = true;
//     int id, fila, col;
//     string posesion;
//     for (int i = 0; i < 6; ++i) {

//         in >> id >> fila >> col >> posesion;
//         estados[i] = make_tuple(id, fila, col, posesion);

//         leerPelota = leerPelota && (posesion == "SIN_PELOTA");
//     }
//     if (leerPelota) {
//         in >> fila >> col;
//         estados[6] = make_tuple(-1, fila, col, "pelota");
//     }
//     return estados;
// }

// std::ostream& operator<<(std::ostream& out, const Equipo &e) {
//     // Envía movimiento de cada jugador
//      // actualiza tablero, prueba jugadas y devuelve la mejor
//     unsigned int i = 0;
//     for (Movimiento& m : turno( generarPosiblesJugadas )) {
//         out << i << " " << m << std::endl;
//         i++;
//     }
// }