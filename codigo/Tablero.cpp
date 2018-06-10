#include "Tablero.hpp"

Tablero::Tablero(const unsigned int &M, const unsigned int &N,
                 const unsigned int &total) : _M(M), _N(N), _total(total) {
    assert(N%2==0 && N >= 2*M);
    // equipoI = make_pair(I, 0);
    // equipoD = make_pair(D, 0);

}

unsigned int Tablero::N() const {return _N;}
unsigned int Tablero::M() const {return _M;}

bool Tablero::pelotaEnPosesion() const {
    return _jugPelota != nullptr;
}

const Jugador& Tablero::jugadorPelota() const {
    assert(pelotaEnPosesion());
    return *_jugPelota;
}

Posicion Tablero::posPelota() const {
    return _pelota.posicion();
}

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

    if (pelotaEnPosesion()) {
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


vector<unsigned int> Tablero::distJugadorAlArco(const bool enDerecha) const {
    const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;
    const unsigned int xArco = (enDerecha) ? _N : -1;

    vector<unsigned int> dist(_jugadoresI.size());

    for (const Jugador &j : js) {
        const Posicion actual = j.pos();

        if (actual.y() > (unsigned int) (_M/2)) {
            dist.push_back(distancia(actual, Posicion(xArco, (unsigned int) (_M/2+1))));
        } else if (actual.y() == _M/2) {
            dist.push_back(abs(int(actual.x()) - int(xArco)));
        } else {
            dist.push_back(distancia(actual, Posicion(xArco, (unsigned int) (_M/2-1))));
        }
    }

    return dist;
}

unsigned int Tablero::distPelotaArco(const bool enDerecha) const {
    const unsigned int xArco = (enDerecha) ? _N : -1;
    const Posicion p = _pelota.posicion();

    if (p.y() > (unsigned int) (_M/2)) {
        return distancia(p, Posicion(xArco, (unsigned int) (_M/2+1)));
    } else if (p.y() == _M/2) {
        return abs(int(p.x()) - int(xArco));
    } else {
        return distancia(p, Posicion(xArco, (unsigned int) (_M/2-1)));
    }
}

unsigned int Tablero::cercaniaARival(const Jugador &j) const {
    // si es el izquierdo, chequear con 3, 4, 5
    // si es el derecho, chequear con 0, 1, 2

    // Por cada rival contrario, ver la distancia con el rival

    // for ()

    return -1;
}

unsigned int Tablero::areaCubierta(const bool enDerecha) const {
    return -1;
}

int Tablero::puntaje(bool enDerecha) const {return -1;}
