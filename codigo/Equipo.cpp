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
                if(_tablero.pelotaEnPosesion() && k > 0) {

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
}}

int Equipo::evaluarTablero(vector<Movimiento> posiblesMovs) { // evalua tablero dado posible combinacion de movs
    vector<int> mediciones(10);     // puede variar el 10
    int puntaje = 0;

    // para cada jugador mío
        vector<int> dist = _tablero.distJugadorAlArco(_en_derecha);
        mediciones[0] = dist[0];
        mediciones[1] = dist[1];
        mediciones[2] = dist[2];


    // if(_en_derecha){


    //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresD[0]);
    //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresD[1]);
    //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresD[2]);
    // } else {
    //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresI[0]);
    //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresI[1]);
    //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresI[2]);

    // }
    mediciones[3] = _tablero.distPelotaArco(_en_derecha);
    int pose = 0;
    // cercanía rival cambia si tengo o no la pelota
    if(_tablero.pelotaEnPosesion() &&
                        ((!_en_derecha && _tablero.jugadorPelota().id() < 3) ||
                         (_en_derecha && _tablero.jugadorPelota().id() >= 3)    )) {  // Tengo la pelota
        pose = _genoma.size()/2;
        // mediciones[4] = cercaniaARival(Jugador&, true);
    } else {
        pose = 0;
        // mediciones[4] = cercaniaARival(Jugador&, false);
    }

    // mediciones[5] = areaCubierta(bool _en_derecha);

    for (int i = 0 ; i < (int)_genoma.size()/2; i++) {      // asume misma longitud
        puntaje += _genoma[i+pose] * mediciones[i];
    }

    return puntaje;
}
