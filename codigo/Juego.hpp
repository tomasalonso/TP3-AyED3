#ifndef __JUEGO__
#define __JUEGO__

#include "Equipo.hpp"
#include "Jugador.hpp"
#include "Pelota.hpp"


class Juego {
public:
    Juego(const unsigned int &M, const unsigned int &N,
            const unsigned int &total);

    void mover();
    void reiniciar(bool enDerecha);
    bool enPosecion() const;
private:
    // Cancha
    const unsigned int _M;
    const unsigned int _N;

    // Tiempos
    const unsigned int _total;
    unsigned int _tiempo;

    // Equipos
    pair<Equipo, unsigned int> _equipoI;
    pair<Equipo, unsigned int> _equipoD;

    // Pelota
    Pelota _pelota;
    Jugador * _jugPelota;
};

#endif
