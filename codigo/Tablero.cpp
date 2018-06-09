#include "Tablero.hpp"

Tablero::Tablero(const unsigned int &M, const unsigned int &N,
                 const unsigned int &total) : _M(M), _N(N), _total(total) {
    equipoI = make_pair(I, 0);
    equipoD = make_pair(D, 0);

}

// Jugador* Pelota::jugador() const {
//     assert(enPosecion());

//     return _j;
// }

// bool Pelota::enPosesion() const {
//     return _j != nullptr;
// }

// void Tablero::mover();

iostream& operator>> (iostream& os, Tablero &j) {
    // tomar movimientos
}

iostream& operator<< (iostream& os, Tablero &j) {
    // imprime estado
}

void Tablero::actualizar() {
    // logica del tablero
}

int Tablero::evaluarTablero(bool enDerecha, Genoma genoma, vector<Movimiento> posiblesMovs) { // evalua tablero dado posible combinacion de movs
    vector<int> mediciones(10);     // puede variar el 10
    int puntaje = 0;

    // para cada jugador mío
    if(enDerecha){
        mediciones[0] = distJugadorAlArco(0);
        mediciones[1] = distJugadorAlArco(1);
        mediciones[2] = distJugadorAlArco(2);
    } else {
        mediciones[0] = distJugadorAlArco(3);
        mediciones[1] = distJugadorAlArco(4);
        mediciones[2] = distJugadorAlArco(5);

    }
    mediciones[3] = distPelotaArco(enDerecha);
    int pose = 0;
    // cercanía rival cambia si tengo o no la pelota
    if(enPosesion() &&
                        (!enDerecha && jugadorPelota().id < 3) ||
                        (enDerecha && jugadorPelota().id >= 3)) {  // Tengo la pelota
        pose = genoma.size()/2;
        mediciones[4] = cercaniaARival(Jugador&, true);
    } else {
        pose = 0;
        mediciones[4] = cercaniaARival(Jugador&, false);
    }

    mediciones[5] = areaCubierta(bool enDerecha);

    for (int i = 0 ; i < genoma.size()/2; i++) {      // asume misma longitud
        puntaje += genoma[i+pose] * mediciones[i];
    }

    return puntaje;
}