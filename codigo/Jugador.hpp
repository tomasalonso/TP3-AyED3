#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicion.hpp"
#include "Pelota.hpp"


class Jugador {
public:
    Jugador(const unsigned int &id, const Posicion &inicial,
            const double &prob_quite);
    unsigned int id() const;
    double probabilidad() const;

    Posicion actual() const;
    Posicion siguiente() const;

    void mover(const Movimiento &m);    // cambia "_siguiente"

    void moverAlCentro(unsigned int n, unsigned int m, bool der);    // mover al centro de la cancha.
    // el bool me dice de qué lado es el equipo y determina el lado del medio

    void actualizar(const Posicion &p); // modifica de prepo

    void reiniciar();                   // vuelve a _inicial

private:
    const unsigned int _id;
    const double _probabilidad_quite;

    const Posicion _inicial;
    Posicion _actual;
    Posicion _siguiente;
};

#endif
