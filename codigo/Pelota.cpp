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

void Pelota::actualizar(const Posicion &p) {
    mover();                                    //la muevo como venia
    if (_siguiente == p) {                      //si solo se movio una vez es que la interceptaron o se movió con el jugador
        _mov = Movimiento(QUIETO);
    } else {
        mover();                                //si no la interceptaron la muevo de nuevo, esta deberia ser la posicion en la que termino si no hubo gol
        if (!(_siguiente == p)) {                  //si no es la posicion, es que hubo gol, la dejo quieta
            _mov = Movimiento(QUIETO);
        }
    }

    _actual = p;                                //le guardo la posicion en la que esta
}