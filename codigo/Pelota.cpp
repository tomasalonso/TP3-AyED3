#include "Pelota.hpp"

#include <cassert>


Pelota::Pelota(const int M, const int N)
    : _mov(QUIETO)
{
    const int medio_x = N/2; // n es par por precondición
    const int medio_y = M/2; // m es impar, así que la celda del centro
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

Posicion Pelota::inicialI() const {
    return _inicialI;
}

Posicion Pelota::inicialD() const {
    return _inicialD;
}

void Pelota::patear(const Movimiento &mov) {
    _mov = mov;
    _siguiente = _actual;
}

void Pelota::mover() {
    _siguiente.mover(_mov);
}

void Pelota::actualizar(const Posicion &p) {
    _actual = p;                                //le guardo la posicion en la que esta
}
