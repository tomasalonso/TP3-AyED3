#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>

class Jugador;

using namespace std;


class Equipo {
public:
    Equipo(const vector<Jugador> jugadores);
    Jugador& jugador(size_t i);
    bool en_derecha() const;
    void reiniciar();
    Equipo& equipo() const;
private:
    vector<Jugador> _jugadores;
    bool _en_derecha;
    Equipo &_equipo;
};

#endif
