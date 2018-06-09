#include "Posicion.hpp"


Posicion::Posicion(const unsigned int x, const unsigned int y) : _x(x), _y(y) {}

Posicion::Posicion(const Posicion& pos) :  _x(pos._x), _y(pos._y) {}

unsigned int Posicion::x() const {
    return _x;
}

unsigned int Posicion::y() const {
    return _y;
}

bool Posicion::operator==(const Posicion otro) const {
    return _x == otro._x && _y == otro._y;
}

void Posicion::mover(const Movimiento &movimiento) {
    if(movimiento.moverse) {
        switch((int)movimiento.dir) {
        case QUIETO: break;
        case ARRIBA:
            _y++; break;
        case ABAJO:
            _y--; break;
        case IZQUIERDA:
            _x--; break;
        case DERECHA:
            _x++; break;
        case ARRIBA_IZQUIERDA:
            _y++; _x--; break;
        case ARRIBA_DERECHA:
            _y++; _x++; break;
        case ABAJO_IZQUIERDA:
            _y--; _x--; break;
        case ABAJO_DERECHA:
            _y--; _x++; break;
        }
    }
}


