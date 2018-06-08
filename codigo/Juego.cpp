#include "Tablero.hpp"

Juego::Juego(const unsigned int &M, const unsigned int &N,
                 const unsigned int &total) : _M(M), _N(N), _total(total) {
    equipoI = make_pair(I, 0);
    equipoD = make_pair(D, 0);

}

Jugador* Pelota::jugador() const {
    assert(enPosecion());

    return _j;
}

bool Pelota::enPosecion() const {
    return _j != nullptr;
}

void mover();
