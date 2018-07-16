#include "Equipo.hpp"

#include <cassert>

Equipo::Equipo(Genoma genoma, bool enDerecha) : _genoma(genoma), _enDerecha(enDerecha) {}


bool Equipo::enDerecha() {
    return _enDerecha;
}


// actualiza tablero, prueba jugadas y devuelve la mejor
vector<Movimiento> Equipo::turno(Tablero &t) {

    vector<vector<Movimiento> > jugadasPropias;
    vector<vector<Movimiento> > jugadasContrario;

    genTodas(t, jugadasContrario, !_enDerecha);
    genTodas(t, jugadasPropias, _enDerecha);

    vector<Movimiento> mejorJugadaContrario = fuerzaBruta(t,
                                jugadasContrario,
                                vector<Movimiento>({
                                                Movimiento(QUIETO),
                                                Movimiento(QUIETO),
                                                Movimiento(QUIETO)
                                            }),
                                !_enDerecha);

    return ( fuerzaBruta(t, jugadasPropias, mejorJugadaContrario, _enDerecha) );
}

// Genera TODAS las jugadas posibles
void Equipo::genTodas(Tablero &t,
                        vector<vector<Movimiento> > &jugadas,
                        bool enDerecha) {
    jugadas.clear();

    vector<vector<Movimiento> > movValidos;

    t.jugadasValidas(movValidos, enDerecha);

    // combinar([[1,2,3],[4,5,6]]) = [1,4], [1,5], [1,6], [2, 4], ...
    jugadas = combinar(movValidos);
}

vector<Movimiento> Equipo::fuerzaBruta(Tablero &t,
                                        const vector<vector<Movimiento> > &jugadasPropias,
                                        const vector<Movimiento> &jugadaContrario,
                                        bool enDerecha) {
    vector<Movimiento> mejorJugada;

    // comparamos todos los movimientos
    int puntajeMejor = -1;
    for (const auto &jPropia : jugadasPropias) {  // Devuelve todas válidas
        t.mover(jPropia, jugadaContrario);

        const int puntajeActual = t.puntaje(_genoma, enDerecha);

        if (puntajeActual > puntajeMejor) {
            puntajeMejor = puntajeActual;
            mejorJugada = jPropia;
        }
    }

    return mejorJugada;
}