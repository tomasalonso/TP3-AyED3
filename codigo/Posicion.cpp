#include "Posicion.hpp"

#include <cmath>


Posicion::Posicion() : _x(0), _y(0) {}

Posicion::Posicion(const int x, const int y) : _x(x), _y(y) {}

Posicion::Posicion(const Posicion& pos) :  _x(pos._x), _y(pos._y) {}

int Posicion::x() const {
    return _x;
}

int Posicion::y() const {
    return _y;
}

bool Posicion::operator==(const Posicion otro) const {
    return _x == otro._x && _y == otro._y;
}

void Posicion::mover(const Movimiento &m) {
    mover(m, 1);
}

void Posicion::mover(const Movimiento &m, const unsigned int i) {
    switch(m.dir()) {
    case QUIETO: break;
    case ARRIBA:
        _y += i; break;
    case ABAJO:
        _y -= i; break;
    case IZQUIERDA:
        _x -= i; break;
    case DERECHA:
        _x += i; break;
    case ARRIBA_IZQUIERDA:
        _y += i; _x -= i; break;
    case ARRIBA_DERECHA:
        _y += i; _x += i; break;
    case ABAJO_IZQUIERDA:
        _y -= i; _x -= i; break;
    case ABAJO_DERECHA:
        _y -= i; _x += i; break;
    }
}


std::istream& operator>>(std::istream& in, Posicion& p) {
    in >> p._x;
    in >> p._y;

    return in;
}

std::ostream& operator<<(std::ostream& out, const Posicion& p) {
    out << p._x << " " << p._y;

    return out;
}


float distancia(const float x1, const float y1, const float x2, const float y2) {
    return sqrt(pow(y1 - y2, 2) + pow(x1 - x2, 2));
}

float altura(const Posicion &a, const Posicion &b, const Posicion &c) {
    const Posicion b_a = Posicion(b.x() - a.x(), b.y() - a.y());
    int d_x = a.x() + b_a.x()/2;
    int d_y = a.y() + b_a.y()/2;

    return distancia(c.x(), c.y(), d_x, d_y);
}
