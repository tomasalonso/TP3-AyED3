#include "Pelota.hpp"

#include <cassert>

Pelota::Pelota(): _posicion(Posicion(0,0)), _tiempo(0), _movimiento(Movimiento((Direccion)0)){}

Posicion Pelota::posicion() const {
    return _posicion;
}

void Pelota::mover(const Movimiento &movimiento, const unsigned int tiempo) {
    _movimiento = movimiento;
    _tiempo = tiempo;
}

void Pelota::actualizar1() {
    if (_tiempo > 0) {
        _posicion.mover(_movimiento);
        _tiempo = 0;
    }
}

void Pelota::actualizar2() {
    if (_tiempo > 0) {
        _posicion.mover(_movimiento);
        _posicion.mover(_movimiento);
        _tiempo--;
    }
}
