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

    genTodas(t, jugadasPropias, _enDerecha);
    genTodas(t, jugadasContrario, !_enDerecha);

    vector<Movimiento> mejorContrario = fuerzaBruta(t,
                                jugadasContrario,
                                vector<Movimiento>({
                                                Movimiento(QUIETO),
                                                Movimiento(QUIETO),
                                                Movimiento(QUIETO)
                                            }),
                                !_enDerecha);

    return ( fuerzaBruta(t, jugadasPropias, mejorContrario, _enDerecha) );
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

    vector<Movimiento> mejorJugada = jugadasPropias[0];
    // comparamos todos los movimientos
    if (enDerecha) {
        t.mover(jugadaContrario, jugadasPropias[0]);
    } else {
        t.mover(jugadasPropias[0], jugadaContrario);
    }

    double puntajeMejor = t.puntaje(_genoma, enDerecha);
    for (unsigned int i = 1; i < jugadasPropias.size(); i++) {  // Devuelve todas válidas
        if (enDerecha) {
            t.mover(jugadaContrario, jugadasPropias[i]);
        } else {
            t.mover(jugadasPropias[i], jugadaContrario);
        }

        const double puntajeActual = t.puntaje(_genoma, enDerecha);

        if (puntajeActual > puntajeMejor) {
            puntajeMejor = puntajeActual;
            mejorJugada = jugadasPropias[i];
        }
    }

    return mejorJugada;
}
