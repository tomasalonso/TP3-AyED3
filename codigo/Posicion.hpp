#ifndef __POSICION__
#define __POSICION__

#include <iostream>

#include "Movimiento.hpp"


class Posicion {
public:
    Posicion();
    Posicion(const int x, const int y);
    Posicion(const Posicion& pos);

    int x() const;
    int y() const;

    void mover(const Movimiento &m);
    void mover(const Movimiento &m, const int intensidad);

    bool operator==(const Posicion otro) const;

    friend std::istream& operator>>(std::istream& in, Posicion& p);
    friend std::ostream& operator<<(std::ostream& out, const Posicion& p);

private:
    int _x;
    int _y;
};


double distancia(const double x1, const double y1, const double x2, const double y2);
double altura(const Posicion &a, const Posicion &b, const Posicion &c);

#endif
