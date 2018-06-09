#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>

class Jugador;

using namespace std;


typedef vector<int> Genoma ;

class Equipo {
public:
    Equipo(Genoma genoma, const vector<Jugador> jugadores);
    // Equipo(const vector<Jugador> jugadores);

    // Para el equipo
    vector<Movimiento> turno(vector<Movimiento> movs); // actualiza tablero, prueba jugadas y devuelve la mejor


    bool esJugadaValida(vector<Movimiento> posiblesMovs);

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
