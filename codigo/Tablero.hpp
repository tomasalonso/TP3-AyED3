#ifndef __TABLERO__
#define __TABLERO__

#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <tuple>

#include "Jugador.hpp"
#include "Pelota.hpp"

using namespace std;


class Tablero {
public:
    // constructor para el árbitro (toma dos equipos)
    Tablero(const int &m, const int &n,
            const unsigned int &total, const vector<Jugador> &eqI,
            const vector<Jugador> &eqD);

    // getters
    int n() const;
    int m() const;

    bool terminado() const;

    bool pelotaEnPosesion() const;
    const Jugador& jugadorPelota() const;
    Posicion posPelota() const;
    // const vector<Jugador>& verJugadores(bool enDerecha) const;


    // Mover al estado siguiente
    void mover(const vector<Movimiento> &movsI,
               const vector<Movimiento> &movsD);
    // Actualizar estado actual
    void actualizar();
    void actualizar(const vector<Movimiento> &movsI,
                    const vector<Movimiento> &movsD);

    void actualizar(vector<Posicion> &posA,
            vector<Posicion> &posB, bool &enPos,
            enum Direccion &posesor, Posicion &posPelota,
            unsigned int &jPelota);


    bool esJugadaValida(vector<Movimiento> posiblesMovs, bool enDerecha);

    void jugadasValidas(vector<vector<Movimiento>> &posiblesI, vector<vector<Movimiento>> &posiblesD);

    unsigned int puntaje();

    // Imprime estado, primero izquierda, despues derecha
    friend std::ostream& operator<<(std::ostream& out, const Tablero &t);

    // // Metodos para evaluarTablero
    // vector<unsigned int> distJugadorAlArco(const bool enDerecha) const;
    // unsigned int distPelotaArco(const bool enDerecha) const;
    // unsigned int cercaniaARival(const Jugador &j) const;
    // float areaCubierta(const bool enDerecha) const;

private:
    bool hayGol();
    // Reinicia a la pos inicial
    void gol();
    bool chequearGol(const Posicion posPelota);


    void moverJug(Jugador& j, Movimiento m);

    bool disputaIntermedia();
    void disputaFinal();

    void desempatar(const vector<Jugador*> &js);
    Jugador* quiteSuelta(Jugador &izq, Jugador &der);
    Jugador* quitePoseida(Jugador &sacador, Jugador &posesor);

    void jugadasValidasJug(const Jugador& j, vector<Movimiento>& movs);


    // Cancha
    const int _m;
    const int _n;

    // Tiempos
    const unsigned int _total;
    unsigned int _tiempo;

    // Equipos
    vector<Jugador> _jugadoresI;
    vector<Jugador> _jugadoresD;

    // Goles
    unsigned int goles_A;
    unsigned int goles_B;

    // Pelota
    Pelota _pelota;
    Jugador * _jugPelota;
    Jugador * _jugPelotaSig;

    // Desempatador (?)
    std::default_random_engine _generador;
    std::uniform_real_distribution<double> _distribucion{0.0,1.0};
};

#endif
