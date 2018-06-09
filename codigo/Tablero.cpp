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
