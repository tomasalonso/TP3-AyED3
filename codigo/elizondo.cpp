#include <iostream>
#include <sstream>
#include <string>

#include "Equipo.hpp"
#include "Tablero.hpp"

using namespace std;


std::istream& operator>>(std::istream& in,
  enum Direccion &d);
void leerEstado(const unsigned int cantJug,
    vector<Posicion> &posA, vector<Posicion> &posB,
    bool &enPos, enum Direccion &posesor, Posicion &posPelota,
    unsigned int &jPelota);


int main() {
    unsigned int m;
    unsigned int n;
    unsigned int total;
    enum Direccion pos;

    cin >> m >> n >> total >> pos;

    vector<unsigned int> probsA;
    vector<unsigned int> probsB;

    unsigned int cantJug = 1;
    unsigned int i;
    unsigned int probabilidad;

    // Lee el probabilidades del equipo 1
    cin >> i >> probabilidad;
    probsA.push_back(probabilidad);
    do {
        cantJug++;

        cin >> i >> probabilidad;
        probsA.push_back(probabilidad);
    } while (i != 0);

    // Lee el probabilidades del equipo 2
    for (unsigned int i = 0; i < cantJug; i++) {
        cin >> i >> probabilidad;
        probsB.push_back(probabilidad);
    }

    // HACER: leer de parámetros
    const vector<Posicion> inicialA({Posicion(1,1),
                                     Posicion(2,2),
                                     Posicion(3,3)
                                    });

    // Arma jugadores primer equipo
    vector<Jugador> jA;
    for (unsigned int i = 0; i < cantJug; i++) {
        jA.push_back(Jugador(i, inicialA[i], probsA[i]));
    }

    // Enviar iniciales
    for (unsigned int i = 0; i < cantJug; i++) {
        cout << i << " " << inicialA[i] << endl;
    }

    // Leo primer estado
    vector<Posicion> posA(cantJug);
    vector<Posicion> posB(cantJug);
    bool enPos;
    enum Direccion posesor;
    Posicion posPelota;
    unsigned int jPelota;

    leerEstado(cantJug, posA, posB, enPos,
        posesor, posPelota, jPelota);

    vector<Jugador> jB;
    for (unsigned int i = 0; i < cantJug; i++) {
        jB.push_back(Jugador(i, posB[i], probsB[i]));
    }

    vector<int> gA({5,5});

    Equipo equipoI(gA, false);

    vector<Jugador> jI((pos == IZQUIERDA) ? jA : jB);
    vector<Jugador> jD((pos == IZQUIERDA) ? jB : jA);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        leerEstado(cantJug, posA, posB, enPos,
            posesor, posPelota, jPelota);
        tablero.actualizar(posA, posB, enPos,
            posesor, posPelota, jPelota);
    }

    return 0;
}

std::istream& operator>>(std::istream& in, enum Direccion &d) {
    string s;
    in >> s;

    if (s == "IZQUIERDA")
     d = IZQUIERDA;
    else d = DERECHA;

    return in;
}

void leerEstado(const unsigned int cantJug,
    vector<Posicion> &posA, vector<Posicion> &posB,
    bool &enPos, enum Direccion &posesor, Posicion &posPelota,
    unsigned int &jPelota) {

    string s;

    enPos = false;
    for (unsigned int i = 0; i < cantJug; i++) {
        unsigned int j;
        cin >> j >> posA[i] >> s;
        if (s == "CON_PELOTA") {
            enPos = true;
            jPelota = j;
            posesor = IZQUIERDA;
        }
    }
    for (unsigned int i = 0; i < cantJug; i++) {
        unsigned int j;
        cin >> j >> posB[i] >> s;
        if (s == "CON_PELOTA") {
            enPos = true;
            jPelota = j;
            posesor = DERECHA;
        }
    }

    if (!enPos) {
        cin >> posPelota;
    }
}