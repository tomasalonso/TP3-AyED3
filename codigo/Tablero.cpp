#include "Tablero.hpp"

#define eqIZQ false
#define eqDER true

using namespace std;


Tablero::Tablero(const int &m, const int &n,
                 const unsigned int &total,
                 const vector<Jugador> &eqI, const vector<Jugador> &eqD)
    : _m(m), _n(n), _total(total), _tiempo(0),
      _jugadoresI(eqI), _jugadoresD(eqD), goles_A(0), goles_B(0),
      _pelota(m, n), _jugPelota(&_jugadoresI[0]) {

    assert(m%2==1);
    assert(n%2==0);
    assert(m >= 3);
    assert(n >= 2*m);

    // arranca el izq
    _jugadoresI[0].moverAlCentro(n, m, eqIZQ);
    _jugPelota = &_jugadoresI[0];
}

int Tablero::n() const {return _n;}
int Tablero::m() const {return _m;}

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

const vector<Jugador>& Tablero::verJugadores(const bool enDerecha) const {
    if (enDerecha) {
        return _jugadoresD;
    }
    return _jugadoresI;
}

pair<unsigned int, unsigned int> Tablero::goles() {
    return make_pair(goles_A, goles_B);
}

bool Tablero::hayGol() {
    // pre: movimiento valido (la pelota no se va afuera de la cancha)
    return (_pelota.siguiente().x() < 0 || _pelota.siguiente().x() > _n);
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
        _jugadoresD[0].moverAlCentro(_n, _m, eqDER);
        _pelota.actualizar(_pelota.inicialI());
        _jugPelota = &_jugadoresD[0];
    } else {
        goles_B++;
        _jugadoresI[0].moverAlCentro(_n, _m, eqIZQ);
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
    if (m.dir() != QUIETO) {
        if (&j == _jugPelota) {
            if (m.esPase()) {
                _pelota.patear(m);
                m = Movimiento(QUIETO);
            } else {
                _pelota.patear(Movimiento(m.dir(), 1)); // Mueve la pelota con el jugador
            }
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

void Tablero::actualizar(const vector<Posicion> &posA, const vector<Posicion> &posB,
                         const bool &enPos, const enum Direccion &posesor,
                         const Posicion &posPelota, const unsigned int &jPelota) {
    _tiempo++;

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
    if ((_pelota.actual().x() > _m-2 || _pelota.actual().x() < 2) &&
        (posPelota == _pelota.inicialI() || posPelota == _pelota.inicialD())) {
        if (posPelota == _pelota.inicialI()) {
            goles_B++;
        } else {
            goles_A++;
        }
        return true;
    }
    return false;
}


std::ostream& operator<<(std::ostream& out, const Tablero &t) {
    cout << "m: " << t._m << endl;
    cout << "n: " << t._n << endl;
    cout << "goles I: " << t.goles_A << endl;
    cout << "goles D: " << t.goles_B << endl;

    for (const Jugador& j : t._jugadoresI) {
        out << j.id() << " " << j.actual().x() << " " << j.actual().y() << " ";
        if (&j == t._jugPelota) {
            out << "CON_PELOTA";
        } else {
            out << "SIN_PELOTA";
        }
        cout << endl;
    }
    for (const Jugador& j : t._jugadoresD) {
        out << j.id() << " " << j.actual().x() << " " << j.actual().y() << " ";
        if (&j == t._jugPelota) {
            out << "CON_PELOTA";
        } else {
            out << "SIN_PELOTA";
        }
        out << endl;
    }
    if (t._jugPelota == nullptr) {
        out << t._pelota.actual().x() << " " << t._pelota.actual().y() << endl;
    }

    return out;
}

// TODO
// evalua tablero dado posible combinacion de movs
unsigned int Tablero::puntaje(Genoma genoma, bool enDerecha) {
    vector<int> mediciones;     // puede variar el 10
    unsigned int puntaje = 0;
    unsigned int index = 0;
    unsigned int cantJug = _jugadoresI.size();
    const bool enPosesion = pelotaEnPosesion() &&
        ((!enDerecha && jugadorPelota().id() < 3) ||
        (enDerecha && jugadorPelota().id() >= 3));
    // para cada jugador mío
    vector<unsigned int> dist = distJugadorAlArco(enDerecha);

    if (enPosesion) {
        // primeros 3 distAlArco si tengo la pelota
        for (const auto& e : dist) {
            puntaje += e * genoma[index++];
        }
        index += cantJug; // salteo los siguientes 3
    } else {
        // segundos 3 distAlArco si no tengo la pelota
        index += cantJug; // salteo los primeros 3
        for (const auto& e : dist) {
            puntaje += e * genoma[index++];
        }
    }

    const auto d = distPelotaArco(enDerecha);
    if (enPosesion) {
        puntaje += d * genoma[index++];
        index++; // salteo el siguiente 1
    } else {
        index++; // salteo el primero 1
        puntaje += d * genoma[index++];
    }

    vector<unsigned int> cercania = cercaniaARival(enDerecha);
    if (enPosesion) {
        for (const auto& e : cercania) {
            puntaje += e * genoma[index++];
        }
        index += cantJug;
    } else {
        for (const auto& e : cercania) {
            puntaje += e * genoma[index++];
        }
        index += cantJug;
    }

    puntaje += areaCubierta(enDerecha) * genoma[index++];

    return puntaje;
}

void Tablero::jugadasValidas(vector<vector<Movimiento>> &posibles,
                            bool enDerecha) {
    vector<Jugador> &js = (enDerecha) ? _jugadoresI : _jugadoresD;

    posibles.clear();
    posibles.resize(js.size());

    for (unsigned int i = 0; i < js.size(); i++) {
        jugadasValidasJug(js[i], posibles[i]);
    }
}

void Tablero::jugadasValidasJug(const Jugador& j, vector<Movimiento>& movs) {
    const bool derecha = j.actual().x()+1 <= _n-1;
    const bool izquierda = j.actual().x()-1 >= 0;
    const bool arriba = j.actual().y()+1 <= _m-1;
    const bool abajo = j.actual().y()+1 >= 0;
    const bool alturaArco = (_m/2)-1 <= j.actual().y() && j.actual().y() <= (_m/2)+1;
    const bool arribaArco = j.actual().y() == (_m/2)+2;
    const bool abajoArco = j.actual().y() == (_m/2)-2;

    movs.push_back(Movimiento(QUIETO));

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
        for (unsigned int dir = 1; dir <= 8; dir++) {
            // Por cada posible intensidad
            for (int inten = 1; inten <= _m/2 ; inten++) {
                Posicion pos = _pelota.actual();
                const Movimiento pase_impar = Movimiento(Direccion(dir), inten*2-1);
                const Movimiento pase_par = Movimiento(Direccion(dir), inten*2);

                pos.mover(pase_impar);
                const bool enArcoImpar =
                    ((_m/2)-1 <= pos.y() && pos.y() <= (_m/2)+1) &&
                    (pos.x() == -1 || pos.x() == _n-1);

                pos = _pelota.actual();
                pos.mover(pase_par);
                const bool enArcoPar =
                    ((_m/2)-1 <= pos.y() && pos.y() <= (_m/2)+1) &&
                    (pos.x() == -1 || pos.x() == _n-1);

                const bool afuera =
                    0 > pos.x() || pos.x() > _n-1 ||
                    0 > pos.y() || pos.y() > _m-1;

                if (afuera && (!enArcoImpar || !enArcoPar)) {
                    break;
                }
                // sis no se va de la cancha
                movs.push_back(pase_par);
            }
        }
    }
}


vector<unsigned int> Tablero::distJugadorAlArco(const bool enDerecha) const {
    const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;
    const unsigned int xArco = (enDerecha) ? _n : -1;

    vector<unsigned int> dist(_jugadoresI.size());

    for (const Jugador &j : js) {
        const float x = j.actual().x();
        const float y = j.actual().y();

        if (y > _m/2) {
            dist.push_back(distancia(x, y, xArco, _m/2+1));
        } else if (y == _m/2) {
            dist.push_back(abs(int(x - xArco)));
        } else {
            dist.push_back(distancia(x, y, xArco, _m/2-1));
        }
    }

    return dist;
}

unsigned int Tablero::distPelotaArco(const bool enDerecha) const {
    const unsigned int xArco = (enDerecha) ? _n : -1;
    const float x = _pelota.actual().x();
    const float y = _pelota.actual().y();

    if (y > (unsigned int) (_m/2)) {
        return distancia(x, y, xArco, _m/2+1);
    } else if (y == _m/2) {
        int res = abs(int(x - xArco));
        return res;
    } else {
        return distancia(x, y, xArco, _m/2-1);
    }
}

vector<unsigned int> Tablero::cercaniaARival(const bool enDerecha) const {
    const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;
    
    vector<unsigned int> cercania; 
    for (const Jugador& j : js) {
        const float x = j.actual().x();
        const float y = j.actual().y();
        const vector<Jugador> &rivales = (j.id() < _jugadoresI.size()) ?
            _jugadoresD : _jugadoresI;

        unsigned int min = distancia(x, y,
                                     rivales[0].actual().x(),
                                     rivales[0].actual().y());
        // Por cada rival contrario, ver la distancia con el rival
        for (unsigned int i = 1; i < rivales.size(); i++) {
            const unsigned int dist = distancia(x, y,
                                         rivales[i].actual().x(),
                                         rivales[i].actual().y());

            if (dist < min) {
                min = dist;
            }
        }
        cercania.push_back(min);
    }

    return cercania;
}

float Tablero::areaCubierta(const bool enDerecha) const {
    const vector<Jugador> &js = (enDerecha) ? _jugadoresD : _jugadoresI;

    const float b = distancia(js[0].actual().x(), js[0].actual().y(),
                                        js[1].actual().x(), js[1].actual().y());

    const float h = altura(js[0].actual(), js[1].actual(), js[2].actual());

    return (b*h)/2;
}