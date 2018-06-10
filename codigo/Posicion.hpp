#ifndef __POSICION__
#define __POSICION__

#include "Movimiento.hpp"


class Posicion {
public:
    Posicion(const unsigned int x, const unsigned int y);
    Posicion(const Posicion& pos);
    unsigned int x() const;
    unsigned int y() const;
    void mover(const Movimiento &movimiento);
    bool operator==(const Posicion otro) const;
private:
    unsigned int _x;
    unsigned int _y;
};

float distancia(const Posicion &p1, const Posicion &p2);

#endif
