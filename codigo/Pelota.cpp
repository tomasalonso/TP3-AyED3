#include "Pelota.hpp"

#include <cassert>


Pelota::Pelota(const unsigned int M, const unsigned int N)
    : _mov(QUIETO)
{
    const unsigned int medio_x = N/2; // n es par por precondición
    const unsigned int medio_y = M/2; // m es impar, así que la celda del centro
                                      // es mitad redondeada para abajo

    _inicialI = Posicion(medio_x-1, medio_y);
    _inicialD = Posicion(medio_x, medio_y);

    _actual = _inicialI;
    _siguiente = _inicialI;
}

Posicion Pelota::actual() const {
    return _actual;
}

Posicion Pelota::siguiente() const {
    return _siguiente;
}

void Pelota::patear(const Movimiento &mov) {
    _mov = mov;
}

void Pelota::mover() {
    // Avanzar UNA posición de acuerdo al pase
    Posicion aux = _actual;
    aux.mover(_mov.dir());

    if (aux == _siguiente) {
        _siguiente.mover(_mov.dir());
    } else {
        _siguiente = aux;
    }
    _mov.mover();
}

void Pelota::actualizar() {
    _actual = _siguiente;
}

void Pelota::reiniciarI() {
    _actual = _inicialI;
    _mov = Movimiento(QUIETO);
}

void Pelota::reiniciarD() {
    _actual = _inicialD;
    _mov = Movimiento(QUIETO);
}
