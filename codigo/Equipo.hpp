#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>
#include <functional>
#include <algorithm>

#include "Movimiento.hpp"
#include "Tablero.hpp"

using namespace std;


typedef vector<int> Genoma;

class Equipo {
public:
    Equipo(Genoma genoma, bool enDerecha);

    // Prueba jugadas y devuelve la mejor
    vector<Movimiento> turno(Tablero &t);

    // Posibles jugadas para evaluar
    void genJugadas1(Tablero &t, vector<vector<Movimiento> > &jugadasPropias,
                     vector<vector<Movimiento> > &jugadasContrario);

    // Para entrenador
    const Jugador& jugador(size_t i) const;
    bool enDerecha();

private:
    Genoma _genoma;
    bool _enDerecha;
};

#endif
