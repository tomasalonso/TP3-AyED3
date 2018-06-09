#ifndef __TABLERO__
#define __TABLERO__


#include "Jugador.hpp"
#include "Pelota.hpp"

#include <tuple>
#include <cassert>
#include <vector>
using namespace std;


class Tablero {
public:
    Tablero(const unsigned int &M, const unsigned int &N,
            const unsigned int &total);

    int N();
    int M();

    void actualizar(vector<Movimiento> movs); // va a tener que saber si hubo gol
    void mover();
    void reiniciar(bool enDerecha);
    bool pelotaEnPosesion() const;
    Posicion posPelota() const;

    int puntaje(bool enDerecha) const;
    const Jugador& jugadorPelota() const;

    const vector<Jugador>& verJugadores(bool enDerecha) const;

    friend ostream& operator>> (ostream& os, Tablero &j); // toma movimientos
    friend ostream& operator<< (ostream& os, Tablero &j); // imprime estado

    // Metodos para evaluarTablero
    vector<int> distJugadorAlArco(bool enDerecha);
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
