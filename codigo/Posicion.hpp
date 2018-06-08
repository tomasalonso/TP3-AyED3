#ifndef __POSICION__
#define __POSICION__

#include "Movimiento.hpp"


class Posicion {
public:
    Posicion(const unsigned int x, const unsigned int y);
    unsigned int x() const;
    unsigned int y() const;
    void mover(const Movimiento &movimiento);
private:
    unsigned int _x;
    unsigned int _y;
};

#endif