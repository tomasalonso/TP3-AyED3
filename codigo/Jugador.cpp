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
    _siguiente.mover(m.dir());
}

void Jugador::moverAlCentro(int n, int m, bool enDerecha) {
    int medio_x = n/2;  // n es par por precondicion
    if (!enDerecha) {
        medio_x--;
    }

    int medio_y = m/2;// m es impar, asi que la celda del centro es mitad redondeada para abajo
    _actual = Posicion(medio_x, medio_y);
}

void Jugador::actualizar() {
    _actual = _siguiente;
}

void Jugador::reiniciar() {
    _actual = _inicial;
}
