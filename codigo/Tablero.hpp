#ifndef __TABLERO__
#define __TABLERO__


#include "Jugador.hpp"
#include "Pelota.hpp"

#include <tuple>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;


class Tablero {
public:
    Tablero(const unsigned int &M, const unsigned int &N,
            const unsigned int &total);

    unsigned int N() const;
    unsigned int M() const;

    bool pelotaEnPosesion() const;
    const Jugador& jugadorPelota() const;
    Posicion posPelota() const;
    const vector<Jugador>& verJugadores(bool enDerecha) const;

    void actualizar(vector<Movimiento> movs, bool enDerecha); // va a tener que saber si hubo gol
    void mover();

    void huboGol(bool goleador); // el bool me dice quién hizo gol;

    void tomarJugadas(bool enDerecha);      // toma movimientos y llama a actualizar

    int puntaje(bool enDerecha) const;

    void imprimirEstado(bool paraEquipoDer); // imprime estado

    // Metodos para evaluarTablero
    vector<unsigned int> distJugadorAlArco(const bool enDerecha) const;
    unsigned int distPelotaArco(const bool enDerecha) const;
    unsigned int cercaniaARival(const Jugador &j) const;
    float areaCubierta(const bool enDerecha) const;

private:

    // Cancha
    const unsigned int _M;
    const unsigned int _N;

    // Tiempos
    const unsigned int _total;
    unsigned int _tiempo;

    // Equipos
    vector<Jugador> _jugadoresI;
    vector<Jugador> _jugadoresD;

    // Goles
    int goles_A;
    int goles_B;

    // Pelota
    Pelota _pelota;
    Jugador * _jugPelota;
};

#endif
