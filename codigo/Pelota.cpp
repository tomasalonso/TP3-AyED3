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

void Pelota::moverAlCentro(int x, int y, bool enDerecha){    // la pongo en el centro, quieta
    int medio_x = x/2;  // n es par por precondicion
    if (!enDerecha) {      // arranca del lado izquierdo
        medio_x--;
    }
    
    int medio_y = y/2;// m es impar, asi que la celda del centro es mitad redondeada para abajo
    _posicion = Posicion(medio_x, medio_y);
    _tiempo = 0;
    _movimiento = QUIETO;
}

void Pelota::actualizar(Posicion &pose) {
    _posicion = pose;
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
