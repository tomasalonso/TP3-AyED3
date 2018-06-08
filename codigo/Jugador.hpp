#ifndef __JUGADOR__
#define __JUGADOR__

#include "Movimiento.hpp"
#include "Posicion.hpp"


class Jugador {
public:
    Jugador(const unsigned int &id, const Posicion &inicial,
            const unsigned int &prob_quite);
    unsigned int id() const;
    unsigned int probabilidad() const;

    void mover(const Movimiento &m);
    void actualizar();
    void reiniciar();
private:
    const unsigned int _id;
    unsigned int _probabilidad_quite;
    Posicion _inicial;
    Posicion _actual;
    Posicion _siguiente;
};

#endif