 #ifndef __TABLERO__
#define __TABLERO__


#include "Jugador.hpp"
#include "Pelota.hpp"

#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <tuple>

using namespace std;


class Tablero {
public:
    // constructor para el árbitro (toma dos equipos)
    Tablero(const unsigned int &M, const unsigned int &N,
            const unsigned int &total, const vector<Jugador> &eqI,
            const vector<Jugador> &eqD);

    // getters
    unsigned int N() const;
    unsigned int M() const;

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


    bool jugadaValida();

    unsigned int puntaje();

    // int puntaje(bool enDerecha) const;

    void imprimirEstado(bool paraEquipoDer); // imprime estado

    // // Metodos para evaluarTablero
    // vector<unsigned int> distJugadorAlArco(const bool enDerecha) const;
    // unsigned int distPelotaArco(const bool enDerecha) const;
    // unsigned int cercaniaARival(const Jugador &j) const;
    // float areaCubierta(const bool enDerecha) const;

private:
    bool hayGol();
    // Reinicia a la pos inicial
    void gol();

    void moverJug(Jugador& j, Movimiento m);

    bool disputaIntermedia();
    void disputaFinal();

    void desempatar(const vector<Jugador*> &js);
    Jugador* quiteSuelta(Jugador &izq, Jugador &der);
    Jugador* quitePoseida(Jugador &sacador, Jugador &posesor);


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
    Jugador * _jugPelotaSig;

    // Desempatador (?)
    std::default_random_engine _generador;
    std::uniform_real_distribution<double> _distribucion{0.0,1.0};
};

#endif
