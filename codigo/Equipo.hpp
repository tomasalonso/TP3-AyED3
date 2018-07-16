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
    vector<Movimiento> turno(Tablero &t, const enum Busqueda opc);

    // Posibles jugadas para evaluar
    void genJugadas1(Tablero &t, vector<vector<Movimiento> > &jugadasPropias,
                     vector<vector<Movimiento> > &jugadasContrario);

    vector<vector<Movimiento> > vecinos(vector<Movimiento> actual, vector<vector<Movimiento> > jugadasValidas);

    vector<Movimiento> fuerzaBruta(Tablero &t);
    vector<Movimiento> busquedaLocal(Tablero &t);
    vector<Movimiento> grasp(Tablero &t);


    // Para entrenador
    const Jugador& jugador(size_t i) const;
    bool enDerecha();

private:
    Genoma _genoma;
    bool _enDerecha;
};

#endif
