#ifndef __PELOTA__
#define __PELOTA__

#include "Posicion.hpp"


class Pelota {
public:
    Pelota();
    Posicion posicion() const;
    void mover(const Movimiento &movimiento, const unsigned int tiempo);
    void moverAlCentro(int x, int y, bool enDerecha);    // la pongo en el centro, quieta
    void actualizar1();
    void actualizar2();
    void actualizar(Posicion pose);
private:
    Posicion _posicion;
    unsigned int _tiempo;
    Movimiento _movimiento;
};

#endif
