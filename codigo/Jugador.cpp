#include "Jugador.hpp"


Jugador::Jugador(const unsigned int &id, const Posicion &inicial,
                 const double &probabilidad_quite) :
    _id(id), _probabilidad_quite(probabilidad_quite), _inicial(inicial),
    _actual(inicial), _siguiente(inicial) {}

unsigned int Jugador::id() const {
    return _id;
}

double Jugador::probabilidad() const {
    return _probabilidad_quite;
}

Posicion Jugador::actual() const {
    return _actual;
}

Posicion Jugador::siguiente() const {
    return _siguiente;
}

void Jugador::mover(const Movimiento &m) {
    _siguiente = _actual;
    _siguiente.mover(m);
}

void Jugador::moverAlCentro(int n, int m, bool der) {
    // pre: n par, m impar
    const int medio_x = (der) ? n/2 : n/2-1;
    // m es impar, asi que la celda del centro es mitad redondeada para abajo
    const int medio_y = m/2;

    _actual = Posicion(medio_x, medio_y);
}

void Jugador::actualizar(const Posicion &p) {
    _actual = p;
}

void Jugador::reiniciar() {
    _actual = _inicial;
}