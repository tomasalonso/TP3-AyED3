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
    vector<Movimiento> turno(Tablero &t, const vector<vector<Movimiento>> &jugadas);

    // Posibles jugadas para evaluar
    vector<vector<Movimiento> > genJugadas1(Tablero &t);

    // Para entrenador
    const Jugador& jugador(size_t i) const;
    bool enDerecha();
    // void reiniciar();

    // COMUNICACION CON ARBITRO
    //-- Toma estado --
    // vector<tuple<int, int, int, string> > leerEstadoArbitro(iostream in);

    //-- Imprime su jugada --
    // void imprimirMovs (vector<Movimiento>& movs);

private:
    Genoma _genoma;
    bool _enDerecha;
};

#endif
