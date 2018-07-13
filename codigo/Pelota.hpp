#ifndef __PELOTA__
#define __PELOTA__

#include "Posicion.hpp"
#include "Movimiento.hpp"


class Pelota {
public:
    Pelota(const unsigned int M, const unsigned int N);

    Posicion actual() const;
    Posicion siguiente() const;

    Posicion inicialI() const;
    Posicion inicialD() const;

    void patear(const Movimiento &mov);
    void mover();

    void actualizar(const Posicion &p);

private:
    Movimiento _mov;

    Posicion _actual;
    Posicion _siguiente;

    Posicion _inicialI;
    Posicion _inicialD;
};

#endif
