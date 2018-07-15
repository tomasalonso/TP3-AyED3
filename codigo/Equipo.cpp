#include "Equipo.hpp"

#include <cassert>
#include "extras.hpp"

Equipo::Equipo(Genoma genoma, bool enDerecha) : _genoma(genoma), _enDerecha(enDerecha) {}


bool Equipo::enDerecha() {
    return _enDerecha;
}

// actualiza tablero, prueba jugadas y devuelve la mejor
vector<Movimiento> Equipo::turno(Tablero &t) {
    vector<Movimiento> mejorJugada;

    vector<vector<Movimiento> > jugadasPropias;
    vector<vector<Movimiento> > jugadasContrario({{Movimiento(QUIETO),
                                                   Movimiento(QUIETO),
                                                   Movimiento(QUIETO)}});


    genJugadas1(t, jugadasPropias, jugadasContrario);

    // generamos de manera todos los movimientos
    // (asumimos que el oponente se queda quieto)
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente
    int puntajeMejor = -1;
    for (auto &jPropia : jugadasPropias) {  // Devuelve todas válidas
        for (auto &jContrario : jugadasContrario) {
            t.mover(jPropia, jContrario);

            const int puntajeActual = t.puntaje();

            if (puntajeActual > puntajeMejor) {
                puntajeMejor = puntajeActual;
                mejorJugada = jPropia;
            }
        }
    }

    return mejorJugada;
}


// Genera TODAS las jugadas posibles
void Equipo::genJugadas1(Tablero &t, vector<vector<Movimiento> > &jugadasPropias, vector<vector<Movimiento> > &jugadasContrario) {
    vector<vector<Movimiento> > movValidosPropios;
    vector<vector<Movimiento> > movValidosContrario;

    jugadasPropias.clear();
    jugadasContrario.clear();

    if (_enDerecha) {
        t.jugadasValidas(movValidosContrario, movValidosPropios);
    } else {
        t.jugadasValidas(movValidosPropios, movValidosContrario);
    }


    jugadasContrario.push_back(vector<Movimiento>(
                                                  {Movimiento(QUIETO),
                                                   Movimiento(QUIETO),
                                                   Movimiento(QUIETO)})
                               );

    jugadasPropias = combinar(movValidosPropios);

}
