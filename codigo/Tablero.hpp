#ifndef __TABLERO__
#define __TABLERO__

#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <tuple>

#include "Jugador.hpp"
#include "Pelota.hpp"
#include "extras.hpp"

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
    const vector<Jugador>& verJugadores(const bool enDerecha) const;

    pair<unsigned int, unsigned int> goles();


    // Mover al estado siguiente
    bool mover(const vector<Movimiento> &movsI,
               const vector<Movimiento> &movsD);
    // Actualizar estado actual
    void actualizar();
    void actualizar(const vector<Movimiento> &movsI,
                    const vector<Movimiento> &movsD);

    void actualizar(const vector<Posicion> &posA, const vector<Posicion> &posB,
                             const bool &enPos, const enum Direccion &posesor,
                    const Posicion &posPelota, const unsigned int &jPelota);


    void jugadasValidas(vector<vector<Movimiento>> &posibles,
                        bool enDerecha);

    double puntaje(Genoma genoma, bool enDerecha);

    // Imprime estado, primero izquierda, despues derecha
    friend std::ostream& operator<<(std::ostream& out, const Tablero &t);
    friend std::ostream& imprimirSiguiente(std::ostream& out, const Tablero &t);


    // Metodos para evaluarTablero
    vector<double> distJugadorAlArco(const bool enDerecha) const;
    double distPelotaArco(const bool enDerecha) const;
    vector<double> cercaniaARival(const bool enDerecha) const;
    double areaCubierta(const bool enDerecha) const;
    vector<double> distJugadorAPelota(const bool enDerecha) const;
    vector<double> distJugadorAlLateral(const bool enDerecha) const;
    void jugadasValidasJug(const Jugador& j, vector<Movimiento>& movs);

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

//    void jugadasValidasJug(const Jugador& j, vector<Movimiento>& movs);


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
