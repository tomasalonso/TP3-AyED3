#include "Jugador.hpp"

Jugador::Jugador(const unsigned int &id, const Posicion &inicial,
                 const unsigned int &probabilidad_quite) :
    _id(id), _probabilidad_quite(probabilidad_quite), _inicial(inicial),
    _actual(inicial), _siguiente(inicial) {}

unsigned int Jugador::id() const {
    return _id;
}

unsigned int Jugador::probabilidad() const {
    return _probabilidad_quite;
}

Posicion Jugador::pos() const {
    return _actual;
}

void Jugador::mover(const Movimiento &m) {
    _siguiente = _actual;
    _siguiente.mover(m);
}

void Jugador::actualizar() {
    _actual = _siguiente;
}

void Jugador::reiniciar() {
    _actual = _inicial;
    _siguiente = _inicial;
}
