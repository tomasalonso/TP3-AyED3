#ifndef __JUGADOR__
#define __JUGADOR__


#include "Posicion.hpp"


class Jugador {
public:
    Jugador(const unsigned int &id, const Posicion &inicial,
            const unsigned int &prob_quite);
    unsigned int id() const;
    unsigned int probabilidad() const;
    const Posicion& pos() const;

    void mover(const Movimiento &m);    // cambia "_siguiente"
    void actualizar();                  // modifica "_actual" al valor de "_siguiente"
    void reiniciar();
private:
    const unsigned int _id;
    unsigned int _probabilidad_quite;
    Posicion _inicial;
    Posicion _actual;
    Posicion _siguiente;
};

#endif
