#ifndef __PELOTA__
#define __PELOTA__

#include "Jugador.hpp"
#include "Movimiento.hpp"
#include "Posicion.hpp"


class Pelota {
public:
    Posicion posicion() const;
    void mover(const Movimiento &movimiento, const unsigned int tiempo);
    void actualizar1();
    void actualizar2();
private:
    Posicion _posicion;
    unsigned int _tiempo;
    Movimiento _movimiento;
};

#endif
