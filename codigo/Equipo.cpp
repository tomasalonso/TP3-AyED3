#include "Equipo.hpp"

#include <cassert>


Equipo::Equipo() {}

Jugador& Equipo::jugador(size_t i) {
    assert(i < _jugadores.size());

    return _jugadores[i];
}

bool Equipo::en_derecha() const {
    return _en_derecha;
}

void Equipo::reiniciar() {
    for (Jugador& j : _jugadores) {
        j.reiniciar();
    }
}
