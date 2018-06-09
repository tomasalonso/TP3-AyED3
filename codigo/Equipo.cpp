#include "Equipo.hpp"

#include <cassert>


Equipo::Equipo(const vector<Jugador> jugadores) {}

Jugador& Equipo::jugador(size_t i) {
    assert(i < _jugadores.size());

    return _jugadores[i];
}

bool Equipo::en_derecha() const {
    return _en_derecha;
}

void Equipo::reiniciar() {
    for (Jugador& j : _jugadores) {
        j.reiniciar();
    }
}

vector<Movimiento> Equipo::turno(vector<Movimiento> movs, function<vector<Movimiento> > generarPosiblesJugadas ){
    _tablero.actualizar(movs);
    vector<Movimiento> mejorJugada;
    // generamos de manera todos los movimientos
    // (asumimos que el oponente se queda quieto)
    vector<vector<Movimiento>> jugadas = generarPosiblesJugadas();
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente

    for (auto &j : jugadas) {       // Devuelve todas válidas
        if (_tablero.evaluarTablero(en_derecha(), genoma, j)) {
            mejorJugada = j;
        }
    }
    return mejorJugada;
}



vector<vector<Movimiento>> genJugadas1() {  // Prueba TODAS las jugadas

    vector<vector<Movimiento>> jugadas;

    int filas = _tablero.M();   // esto no lo puedo acceder
    int totalDirs = 10;
    // Por cada jugada jugador 1
    for (int i = 0; i < totalDirs; ++i) {
        // Por cada jugada jugador 2
        for (int j = 0; j < totalDirs; ++j) {
            // Por cada jugada jugador 3
            for (int k = 0; k < totalDirs; ++k) {
                // Todos se mueven
                vector<Movimiento> jugada = {Movimiento(i), Movimiento(j) , Movimiento(k)}

                if(esJugadaValida(jugada)) {
                    jugadas.push_back(jugada);
                }
                if(_tablero.enPosesion() && k > 0) {

                    int idJugadorPelota = (_tablero.jugadorPelota()).id;
                    if(idJugadorPelota < 4) {   // es de mi equipo

                        // Por cada posible intensidad
                        for (int inten = 0; inten < filas/2; ++inten) {
                            jugada[idJugadorPelota] = Movimiento(k,inten);
                            if(esJugadaValida(jugada)) {
                                jugadas.push_back(jugada);
                            }
                        }
                    }
                }
            }

        }
    }
    return jugadas;
}