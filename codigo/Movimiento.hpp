#ifndef __MOVIMIENTO__
#define __MOVIMIENTO__

#include <cassert>
#include <iostream>

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

class Movimiento {
public:
    Movimiento() : _dir(QUIETO) {};
    Movimiento(Direccion d) : _dir(d), _intensidad(0) {};
    Movimiento(Direccion d, unsigned int i) : _dir(d), _intensidad(i) {
        assert(d != QUIETO);
    }

    bool esPase() const {
        return (_intensidad > 0);
    }

    Direccion dir() const {
        return _dir;
    }

    void avanzar() {
        if (_intensidad > 0) {
            _intensidad--;
        } else {
            _dir = QUIETO;
        }
    }

private:
    Direccion _dir;
    unsigned int _intensidad;
};


// std::ostream& operator<<(std::ostream& out, const Direccion &d) {
//     out << (unsigned int) d;

//     return out;
// }

// std::istream& operator>>(std::istream& in, Direccion &d) {
//     unsigned int e;

//     in >> e;

//     d = static_cast<Direccion>(e);

//     return in;
// }

#endif
