#ifndef __MOVIMIENTO__
#define __MOVIMIENTO__
#include <cassert>

enum Direccion {
    QUIETO = 0,
    ARRIBA = 2,
    ABAJO = 6,
    IZQUIERDA = 8,
    DERECHA = 4,
    ARRIBA_IZQUIERDA = 1,
    ARRIBA_DERECHA = 3,
    ABAJO_IZQUIERDA = 7,
    ABAJO_DERECHA = 5
};

struct Movimiento {
    Movimiento(Direccion d) : moverse(1), dir(d), intensidad(-1) {};
    Movimiento(Direccion d, int i) : moverse(0), dir(d), intensidad(i) {
        assert(d != QUIETO);
    }

    bool moverse;   // 0-> movimiento, 1-> tirar
    Direccion dir;
    int intensidad;
};
// Constructores
// Movimiento::Movimiento(Direccion d) : moverse(1), dir(d), intensidad(-1) {}
// Movimiento::Movimiento(Direccion d, int i) : moverse(0), dir(d), intensidad(i) {
//     assert(d != QUIETO);
// }


#endif
