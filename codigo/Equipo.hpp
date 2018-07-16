#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>
#include <functional>
#include <algorithm>

#include "Movimiento.hpp"
#include "Tablero.hpp"
#include "extras.hpp"

using namespace std;


class Equipo {
public:
    Equipo(Genoma genoma, bool enDerecha);

    // Prueba jugadas y devuelve la mejor
    vector<Movimiento> turno(Tablero &t);

    // Posibles jugadas para evaluar
    void genTodas(Tablero &t,
                    vector<vector<Movimiento> > &jugadas,
                    bool enDerecha);

    vector<Movimiento> fuerzaBruta(Tablero &t,
                                    const vector<vector<Movimiento> > &jugadasPropias,
                                    const vector<Movimiento> &jugadaContrario,
                                    bool enDerecha);

    // Para entrenador
    const Jugador& jugador(size_t i) const;
    bool enDerecha();

private:
    Genoma _genoma;
    bool _enDerecha;
};

#endif
