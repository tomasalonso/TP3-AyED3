#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>
#include <functional>
#include <algorithm>

#include "Tablero.hpp"

class Jugador;
class Tablero;

using namespace std;


typedef vector<int> Genoma ;

class Equipo {
public:
    Equipo(Genoma genoma, const vector<Jugador> jugadores,
            const unsigned int &M, const unsigned int &N,
            const unsigned int &total, bool enDerecha);
    // Equipo(const vector<Jugador> jugadores);

    // Para el equipo
    vector<Movimiento> turno(vector<Movimiento> movs, // actualiza tablero, prueba jugadas y devuelve la mejor
                             function<vector<vector<Movimiento>> (void) > generarPosiblesJugadas );


    bool esJugadaValida(vector<Movimiento> posiblesMovs);

    int evaluarTablero(vector<Movimiento> posiblesMovs); // evalua tablero dado posible combinacion de movs

    // Posibles jugadas para evaluar
    vector<vector<Movimiento>> genJugadas1();

    // Para entrenador
    Jugador& jugador(size_t i);
    bool en_derecha();
    void reiniciar();

private:
    Genoma _genoma;
    bool _en_derecha;
    Tablero _tablero;
};

#endif
