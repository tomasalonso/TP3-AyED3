#include "Tablero.hpp"

Tablero::Tablero(const unsigned int &M, const unsigned int &N,
                 const unsigned int &total) : _M(M), _N(N), _total(total) {
    assert(N%2==0 && N >= 2*M);
    // equipoI = make_pair(I, 0);
    // equipoD = make_pair(D, 0);

}

Posicion Tablero::posPelota() const {
    return _pelota.posicion();
}

// Jugador* Pelota::jugador() const {
//     assert(enPosecion());

//     return _j;
// }

// bool Pelota::enPosesion() const {
//     return _j != nullptr;
// }

// void Tablero::mover();

const vector<Jugador>& Tablero::verJugadores(bool enDerecha) const {
    if (enDerecha) {
        return _jugadoresD;
    }
    return _jugadoresI;
}

void Tablero::tomarJugadas(bool enDerecha) {
    int id;
    string tipoMov;
    int direccion;
    vector<Movimiento> movs(3, Movimiento(QUIETO));
    for (int i = 0; i < 3; i++) {
        cin >> id >> tipoMov >> direccion;
        if(tipoMov == "MOVIMIENTO") {
            movs[i] = Movimiento((Direccion)direccion);
        } else if(tipoMov == "PASE") {
            int intensidad;
            cin >> intensidad;
            movs[i] = Movimiento((Direccion)direccion, intensidad);
        }
    }
    actualizar(movs,enDerecha);
}

void Tablero::imprimirEstado(bool paraEquipoDer) {
    const vector<Jugador>& eqIzq = verJugadores(false);;
    const vector<Jugador>& eqDer = verJugadores(true);;
    vector<pair<Posicion,unsigned int> > jugadores;

    int i = 0;
    if (paraEquipoDer) {
        for (i = 0; i < 3; i++) {
            jugadores.push_back(make_pair(eqDer[i].pos(),eqDer[i].id()));

            // [i] = eqDer[i];
        }
        for (i = 3; i < 6; i++) {
            jugadores.push_back(make_pair(eqIzq[i].pos(),eqIzq[i].id()));
            // jugadores[i] = eqIzq[i%3];
        }
    } else {
        for (i = 0; i < 3; i++) {
            jugadores.push_back(make_pair(eqIzq[i].pos(),eqIzq[i].id()));
            // jugadores[i] = eqIzq[i%3];

        }
        for (i = 3; i < 6; i++) {
            jugadores.push_back(make_pair(eqDer[i].pos(),eqDer[i].id()));
            // [i] = eqDer[i];
        }
    }

    if(pelotaEnPosesion()) {
        const Jugador& jugPelota = jugadorPelota();
        int j = 0;
        for (auto jugador : jugadores) {
            if (jugador.second == jugPelota.id()) {
                printf("%i %i %i %s\n", j, jugador.first.y(), jugador.first.x(),"CON_PELOTA" );
            } else {
                printf("%i %i %i %s\n", j, jugador.first.y(), jugador.first.x(),"SIN_PELOTA" );
            }
            j++;
        }
    } else {
        int j = 0;
        for (auto jugador : jugadores) {
            printf("%i %i %i %s\n", j, jugador.first.y(), jugador.first.x(),"SIN_PELOTA" );
            j++;
        }
        printf("%i %i\n", posPelota().y(), posPelota().x() );
    }
}

void Tablero::actualizar(vector<Movimiento> movs, bool enDerecha) {
    // logica del tablero
}


vector<int> Tablero::distJugadorAlArco(bool enDerecha) { vector<int>  v; return v;}
int Tablero::distPelotaArco(bool enDerecha) {return -1;}
int Tablero::cercaniaARival(Jugador&) {return -1;}
int Tablero::areaCubierta(bool enDerecha) {return -1;}
bool Tablero::pelotaEnPosesion() const {return false;}

int Tablero::puntaje(bool enDerecha) const {return -1;}
const Jugador& Tablero::jugadorPelota() const {return _jugadoresI[0];}
int Tablero::N(){return _N;}
int Tablero::M(){return _M;}