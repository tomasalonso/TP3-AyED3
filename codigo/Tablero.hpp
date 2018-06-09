#ifndef __TABLERO__
#define __TABLERO__

#include "Equipo.hpp"
#include "Jugador.hpp"
#include "Pelota.hpp"
#include <pair>

class Tablero {
public:
    Juego(const unsigned int &M, const unsigned int &N,
            const unsigned int &total);

    void actualizar(vector<Movimiento> movs); // va a tener que saber si hubo gol
    void mover();
    void reiniciar(bool enDerecha);
    bool enPosesion() const;

    int puntaje(bool enDerecha) const;
    Jugador& jugadorPelota() const;

    int evaluarTablero(bool enDerecha, Genoma genoma, vector<Movimiento> posiblesMovs); // evalua tablero dado posible combinacion de movs

    friend ostream& operator>> (ostream& os, Juego &j); // toma movimientos
    friend ostream& operator<< (ostream& os, Juego &j); // imprime estado

    // Metodos para evaluarTablero
    int distJugadorAlArco(Jugador&);
    int distPelotaArco(bool enDerecha);
    int cercaniaARival(Jugador&);
    int areaCubierta(bool enDerecha);


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
