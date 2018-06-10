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
        const float x = j.pos().x();
        const float y = j.pos().y();

        if (y > _M/2) {
            dist.push_back(distancia(x, y, xArco, _M/2+1));
        } else if (y == _M/2) {
            dist.push_back(abs(x - xArco));
        } else {
            dist.push_back(distancia(x, y, xArco, _M/2-1));
        }
    }

    return dist;
}

unsigned int Tablero::distPelotaArco(const bool enDerecha) const {
    const unsigned int xArco = (enDerecha) ? _N : -1;
    const float x = _pelota.posicion().x();
    const float y = _pelota.posicion().y();

    if (y > (unsigned int) (_M/2)) {
        return distancia(x, y, xArco, _M/2+1);
    } else if (y == _M/2) {
        return abs(x - xArco);
    } else {
        return distancia(x, y, xArco, _M/2-1);
    }
}

unsigned int Tablero::cercaniaARival(const Jugador &j) const {
    const float x = j.pos().x();
    const float y = j.pos().y();
    const vector<Jugador> &rivales = (j.id() < _jugadoresI.size()) ?
        _jugadoresD : _jugadoresI;

    unsigned int min = distancia(x, y,
                                 rivales[0].pos().x(), rivales[0].pos().y());
    // Por cada rival contrario, ver la distancia con el rival
    for (size_t i = 1; i < rivales.size(); i++) {
        unsigned int dist = distancia(x, y,
                                      rivales[i].pos().x(), rivales[i].pos().y());

        if (dist < min) {
            min = dist;
        }
    }

    return min;
}

float Tablero::areaCubierta(const bool enDerecha) const {
    const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;

    const float b = distancia(js[0].pos().x(), js[0].pos().y(),
                                        js[1].pos().x(), js[1].pos().y());

    const float h = altura(js[0].pos(), js[1].pos(), js[2].pos());

    return (b*h)/2;
}

int Tablero::puntaje(bool enDerecha) const {return -1;}
