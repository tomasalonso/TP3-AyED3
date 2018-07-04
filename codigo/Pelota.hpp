#ifndef __PELOTA__
#define __PELOTA__

#include "Posicion.hpp"
#include "Movimiento.hpp"


class Pelota {
public:
    Pelota(const unsigned int M, const unsigned int N);

    Posicion actual() const;
    Posicion siguiente() const;

    void patear(const Movimiento &mov);
    void mover();

    void actualizar();

    void reiniciarI();    // la pongo en el centro, para el equipo I
    void reiniciarD();    // la pongo en el centro, para el equipo D

private:
    Movimiento _mov;

    Posicion _actual;
    Posicion _siguiente;

    Posicion _inicialI;
    Posicion _inicialD;
};

#endif
