#include "Tablero.hpp"

#define eqIZQ false
#define eqDER true

using namespace std;


Tablero::Tablero(const int &M, const int &N,
                 const unsigned int &total,
                 const vector<Jugador> &eqI, const vector<Jugador> &eqD)
    : _M(M), _N(N), _total(total), _tiempo(0),
      _jugadoresI(eqI), _jugadoresD(eqD), goles_A(0), goles_B(0),
      _pelota(M, N), _jugPelota(&_jugadoresI[0]) {

    assert(M%2==1);
    assert(N%2==0);
    assert(M >= 3);
    assert(N >= 2*M);

    // arranca el izq
    _jugadoresI[0].moverAlCentro(N, M, eqIZQ);
    _jugPelota = &_jugadoresI[0];
}

int Tablero::N() const {return _N;}
int Tablero::M() const {return _M;}

bool Tablero::terminado() const {
    return (_tiempo == _total);
}

bool Tablero::pelotaEnPosesion() const {
    return _jugPelota != nullptr;
}

const Jugador& Tablero::jugadorPelota() const {
    assert(pelotaEnPosesion());

    return *_jugPelota;
}

Posicion Tablero::posPelota() const {
    return _pelota.actual();
}

// const vector<Jugador>& Tablero::verJugadores(bool enDerecha) const {
//     if (enDerecha) {
//         return _jugadoresD;
//     }
//     return _jugadoresI;
// }

bool Tablero::hayGol() {
    // pre: movimiento valido (la pelota no se va afuera de la cancha)
    return (_pelota.siguiente().x() < 0 || _pelota.siguiente().x() > _N);
}

void Tablero::gol() {
    // pre: hayGol()
    assert(hayGol());

    for (Jugador& j : _jugadoresI) {
        j.reiniciar();
    }
    for (Jugador& j : _jugadoresD) {
        j.reiniciar();
    }

    // Gol equipo derecha
    if (_pelota.siguiente().x() < 0) {
        goles_A++;
        _jugadoresD[0].moverAlCentro(_N, _M, eqDER);
        _pelota.actualizar(_pelota.inicialI());
        _jugPelota = &_jugadoresD[0];
    } else {
        goles_B++;
        _jugadoresI[0].moverAlCentro(_N, _M, eqIZQ);
        _pelota.actualizar(_pelota.inicialD());
        _jugPelota = &_jugadoresI[0];
    }
}

void Tablero::mover(const vector<Movimiento> &movsI, const vector<Movimiento> &movsD) {
    // Pre: movimiento válido

    // MoverJugadores
    // Mueven a siguiente y si tiene la pelota la puede patear
    for (unsigned int i = 0; i < movsI.size(); i++) {
        moverJug(_jugadoresI[i], movsI[i]);
        moverJug(_jugadoresD[i], movsD[i]);
    }

    // MoverPelota
    // En moverJugadores un jugador puede patear o mover la pelota
    _pelota.mover();
    // Si la tiene un jugador se queda quieta, si la patearon se mueve UNA pos
    if (!disputaIntermedia()) {
        // Si no hubo intersección
        // Mueve la segunda pos del turno
        _pelota.mover();
        disputaFinal();
    }
}

void Tablero::moverJug(Jugador& j, Movimiento m) {
    // si tiene la pelota
    if (&j == _jugPelota) {
        if (m.esPase()) {
            _pelota.patear(m);
            m = Movimiento(QUIETO);
        } else {
            _pelota.patear(Movimiento(m.dir(), 1)); // Mueve la pelota con el jugador
        }
    }
    j.mover(m);
}

bool Tablero::disputaIntermedia() {
    // Hay que chequear si el jugador se movió y es casillero intermedio, si se
    // movió no hay disputa
    vector<Jugador*> js;

    // Busca los jugadores que estén en el mismo casillero que la pelota
    for (unsigned int i = 0; i < _jugadoresI.size(); i++) {
        Jugador& jI = _jugadoresI[i];
        Jugador& jD = _jugadoresD[i];

        if (jI.siguiente() == jI.actual() && // Si no se movió
            jI.siguiente() == _pelota.siguiente()) {
            js.push_back(&jI);
        }
        if (jD.siguiente() == jD.actual() &&
            jD.siguiente() == _pelota.siguiente()) {
            js.push_back(&jD);
        }
    }

    if (js.size() > 0) {
        desempatar(js);
    }

    return (js.size() > 0);
}

void Tablero::disputaFinal() {
    // Si es casillero final, hay disputa aunque se hayan movido
    vector<Jugador*> js;

    for (unsigned int i = 0; i < _jugadoresI.size(); i++) {
        Jugador& jI = _jugadoresI[i];
        Jugador& jD = _jugadoresD[i];

        if (jI.siguiente() == _pelota.siguiente()) {
            js.push_back(&jI);
        }
        if (jD.siguiente() == _pelota.siguiente()) {
            js.push_back(&jD);
        }
    }

    if (js.size() > 0) {
        desempatar(js);
    }
}

void Tablero::desempatar(const vector<Jugador*>& js) {
    if (js.size() == 1) {
        _jugPelotaSig = js[0];
    } else { // if (js.size() == 2)
        // desempatar
        if (_jugPelota == nullptr) { // si nadie tiene la pelota
            _jugPelota = quiteSuelta(*js[0], *js[1]);
        } else {
            _jugPelota = quitePoseida(
                         (js[0] != _jugPelota) ? *js[0] : *js[1],
                         (js[0] == _jugPelota) ? *js[0] : *js[1]
                                      );
        }
    }
}

Jugador* Tablero::quiteSuelta(Jugador &izq, Jugador &der) {
    double probaIzq = double(izq.probabilidad());
    double probaDer = double(der.probabilidad());

  	double numero = _distribucion(_generador);

    bool gana = (numero <= (probaIzq / (probaIzq + probaDer)));

    if (gana) {
        return &izq;
    }
    return &der;
}

Jugador* Tablero::quitePoseida(Jugador &sacador, Jugador &posesor) {
    double probaPosedor = double(posesor.probabilidad());
    double probaSacador = double(sacador.probabilidad());

    double numero = _distribucion(_generador);

    bool quita = (numero <= (probaSacador/(probaSacador + (1-probaPosedor))));

    if (quita) {
        return &sacador;
    }

    return &posesor;
}

void Tablero::actualizar() {
    // pre: se movió previamente
    if (hayGol()) {
        gol(); // Se reinician las posiciones
    } else {
        // actual = siguiente
        // Actualizar jugadores
        for (Jugador& j : _jugadoresI) {
            j.actualizar(j.siguiente());
        }
        for (Jugador& j : _jugadoresD) {
            j.actualizar(j.siguiente());
        }

        _pelota.actualizar(_pelota.siguiente());
    }
    _jugPelota = _jugPelotaSig;

    _tiempo++;
}

void Tablero::actualizar(const vector<Movimiento> &movsI,
                         const vector<Movimiento> &movsD) {
    // Pre: movimiento válido
    mover(movsI, movsD);
    actualizar();
}

void Tablero::actualizar(vector<Posicion> &posA,
        vector<Posicion> &posB, bool &enPos,
        enum Direccion &posesor, Posicion &posPelota,
        unsigned int &jPelota) {
    _tiempo--;

    // Equipos
    for (unsigned int i = 0; i < _jugadoresI.size(); i++) {
        _jugadoresI[i].actualizar(posA[i]);
        _jugadoresD[i].actualizar(posB[i]);
    }

    if (!chequearGol(posPelota)) {
        // si no hubo gol, actualiza la pelota
        if (enPos) {
            _jugPelota = (posesor == IZQUIERDA) ?
                    &_jugadoresI[jPelota] : &_jugadoresD[jPelota];
            _pelota.actualizar(posPelota);
        } else {
            _pelota.mover();
            _pelota.mover();
        }
    }
}

bool Tablero::chequearGol(const Posicion posPelota) {
    if((_pelota.actual().x() > _M-2 || _pelota.actual().x() < 2) &&
        (posPelota == _pelota.inicialI() || posPelota == _pelota.inicialD())) {
        if(posPelota == _pelota.inicialI()) {
            goles_B++;
        } else {
            goles_A++;
        }
        return true;
    }
    return false;
}


std::ostream& operator<<(std::ostream& out, const Tablero &t) {
    for (const Jugador& j : t._jugadoresI) {
        out << j.id() << " " << j.siguiente().x() << " " << j.siguiente().y() << " ";
        if (&j == t._jugPelotaSig) {
            out << "CON_PELOTA";
        } else {
            out << "SIN_PELOTA";
        }
        cout << endl;
    }
    for (const Jugador& j : t._jugadoresD) {
        out << j.id() << " " << j.siguiente().x() << " " << j.siguiente().y() << " ";
        if (&j == t._jugPelotaSig) {
            out << "CON_PELOTA";
        } else {
            out << "SIN_PELOTA";
        }
        out << endl;
    }
    if (t._jugPelotaSig == nullptr) {
        out << t._pelota.siguiente().x() << " " << t._pelota.siguiente().y() << endl;
    }

    return out;
}

// TODO
unsigned int Tablero::puntaje() { // evalua tablero dado posible combinacion de movs
    return 0;
//     vector<int> mediciones(10);     // puede variar el 10
//     int puntaje = 0;

//     // para cada jugador mío
//         vector<unsigned int> dist = _tablero.distJugadorAlArco(_en_derecha);
//         mediciones[0] = dist[0];
//         mediciones[1] = dist[1];
//         mediciones[2] = dist[2];


//     // if(_en_derecha){


//     //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresD[0]);
//     //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresD[1]);
//     //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresD[2]);
//     // } else {
//     //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresI[0]);
//     //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresI[1]);
//     //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresI[2]);

//     // }
//     mediciones[3] = _tablero.distPelotaArco(_en_derecha);
//     int pose = 0;

//     // cercanía rival cambia si tengo o no la pelota
//     // Si tengo la pelota
//     if(_tablero.pelotaEnPosesion() &&
//                         ((!_en_derecha && _tablero.jugadorPelota().id() < 3) ||
//                          (_en_derecha && _tablero.jugadorPelota().id() >= 3)    )) {
//         pose = _genoma.size()/2;
//         // mediciones[4] = cercaniaARival(Jugador&, true);
//     } else {
//         pose = 0;
//         // mediciones[4] = cercaniaARival(Jugador&, false);
//     }

//     // mediciones[5] = areaCubierta(bool _en_derecha);

//     for (int i = 0 ; i < (int)_genoma.size()/2; i++) {      // asume misma longitud
//         puntaje += _genoma[i+pose] * mediciones[i];
//     }

//     return puntaje;
}

void Tablero::jugadasValidas(vector<vector<Movimiento>> &posiblesI, vector<vector<Movimiento>> &posiblesD) {
    posiblesI.clear();
    posiblesD.clear();

    // por cada jugador de I
    for (unsigned int i = 0; i < _jugadoresI.size(); i++) {

        posiblesI.push_back(vector<Movimiento>());
        posiblesD.push_back(vector<Movimiento>());
        
        jugadasValidasJug(_jugadoresI[i], posiblesI[i]);
        jugadasValidasJug(_jugadoresD[i], posiblesD[i]);
    }

    for (Jugador& j : _jugadoresI) {
        
    }
    //
}

void Tablero::jugadasValidasJug(const Jugador& j, vector<Movimiento>& movs) {
    movs.push_back(Movimiento(QUIETO)); 

    const bool derecha = j.actual().x()+1 <= _M-1;
    const bool izquierda = j.actual().x()-1 >= 0;
    const bool arriba = j.actual().y()+1 <= _N-1;
    const bool abajo = j.actual().y()+1 >= 0;
    const bool alturaArco = (_m/2)-1 <= j.actual().y() <= (m/2)+1;
    const bool arribaArco = j.actual().y() == (m/2)+2;
    const bool abajoArco = j.actual().y() == (m/2)-2;

    if(derecha)
        movs.push_back(Movimiento(DERECHA));

    if(izquierda)
        movs.push_back(Movimiento(IZQUIERDA));

    if(arriba)
        movs.push_back(Movimiento(ARRIBA));

    if(abajo)
        movs.push_back(Movimiento(ABAJO));

    if(arriba && izquierda)
        movs.push_back(Movimiento(ARRIBA_IZQUIERDA));

    if(arriba && derecha)
        movs.push_back(Movimiento(ARRIBA_DERECHA));

    if(abajo && izquierda)
        movs.push_back(Movimiento(ABAJO_IZQUIERDA));

    if(abajo && derecha)
        movs.push_back(Movimiento(ABAJO_DERECHA));

    // si tiene la pelota
    if (_jugPelota == &j) {
        if(!derecha && alturaArco) {
            movs.push_back(Movimiento(DERECHA));
        } else if (!derecha && arribaArco){
            movs.push_back(Movimiento(ABAJO_DERECHA));
        } else if (!derecha && abajoArco) {
            movs.push_back(Movimiento(ARRIBA_DERECHA));
        } else if (!izquierda && alturaArco) {
            movs.push_back(Movimiento(IZQUIERDA));
        } else if (!izquierda && arribaArco){
            movs.push_back(Movimiento(ABAJO_IZQUIERDA));
        } else if (!izquierda && abajoArco) {
            movs.push_back(Movimiento(ARRIBA_IZQUIERDA));
        }
        for (unsigned int dir = 1; dir < 9; dir++) {
            // Por cada posible intensidad
            for (unsigned int inten = 0; inten < _M/2 && !intensidadTope; inten++) {
                //HACER: agregar las intensidades hasta que se vaya arafue de la chacan

            }
        }
    }
}


// bool Tablero::enArco(int n, int m, const Posicion& pos) {
//     vector<Posicion> posDeArco(6,Posicion(-1,-1));

//     int mitadArco = (m/2);  // celda del medio, el arco mide tres celdas

//     posDeArco[0] = Posicion(-1, mitadArco +1);
//     posDeArco[1] = Posicion(-1, mitadArco);
//     posDeArco[2] = Posicion(-1, mitadArco -1);
//     posDeArco[3] = Posicion(n, mitadArco +1);
//     posDeArco[4] = Posicion(n, mitadArco);
//     posDeArco[5] = Posicion(n, mitadArco -1);

//     return 1 == count(posDeArco.begin(), posDeArco.end(), pos);
// }



// vector<unsigned int> Tablero::distJugadorAlArco(const bool enDerecha) const {
//     const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;
//     const unsigned int xArco = (enDerecha) ? _N : -1;

//     vector<unsigned int> dist(_jugadoresI.size());

//     for (const Jugador &j : js) {
//         const float x = j.pos().x();
//         const float y = j.pos().y();

//         if (y > _M/2) {
//             dist.push_back(distancia(x, y, xArco, _M/2+1));
//         } else if (y == _M/2) {
//             dist.push_back(abs(int(x - xArco)));
//         } else {
//             dist.push_back(distancia(x, y, xArco, _M/2-1));
//         }
//     }

//     return dist;
// }

// unsigned int Tablero::distPelotaArco(const bool enDerecha) const {
//     const unsigned int xArco = (enDerecha) ? _N : -1;
//     const float x = _pelota.posicion().x();
//     const float y = _pelota.posicion().y();

//     if (y > (unsigned int) (_M/2)) {
//         return distancia(x, y, xArco, _M/2+1);
//     } else if (y == _M/2) {
//         int res = abs(int(x - xArco));
//         return res;
//     } else {
//         return distancia(x, y, xArco, _M/2-1);
//     }
// }

// unsigned int Tablero::cercaniaARival(const Jugador &j) const {
//     const float x = j.pos().x();
//     const float y = j.pos().y();
//     const vector<Jugador> &rivales = (j.id() < _jugadoresI.size()) ?
//         _jugadoresD : _jugadoresI;

//     unsigned int min = distancia(x, y,
//                                  rivales[0].pos().x(), rivales[0].pos().y());
//     // Por cada rival contrario, ver la distancia con el rival
//     for (size_t i = 1; i < rivales.size(); i++) {
//         unsigned int dist = distancia(x, y,
//                                       rivales[i].pos().x(), rivales[i].pos().y());

//         if (dist < min) {
//             min = dist;
//         }
//     }

//     return min;
// }

// float Tablero::areaCubierta(const bool enDerecha) const {
//     const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;

//     const float b = distancia(js[0].pos().x(), js[0].pos().y(),
//                                         js[1].pos().x(), js[1].pos().y());

//     const float h = altura(js[0].pos(), js[1].pos(), js[2].pos());

//     return (b*h)/2;
// }

// int Tablero::puntaje(bool enDerecha) const {return -1;}
