#ifndef __EQUIPO__
#define __EQUIPO__

#include <vector>
#include <functional>
#include <algorithm>

#include "Tablero.hpp"

class Jugador;
class Tablero;

using namespace std;


typedef vector<int> Genoma;
bool enArco(int n, int m, const Posicion& pos);

class Equipo {
public:
    Equipo(Genoma genoma, bool enDerecha);

    // Prueba jugadas y devuelve la mejor
    vector<Movimiento> turno(Tablero &t, const vector<vector<Movimiento>> &jugadas);

    // Posibles jugadas para evaluar
    vector<vector<Movimiento> > genJugadas1();

    // Para entrenador
    const Jugador& jugador(size_t i) const;
    bool enDerecha();
    // void reiniciar();

    // COMUNICACION CON ARBITRO
    //-- Toma estado --
    // vector<tuple<int, int, int, string> > leerEstadoArbitro(iostream in);

    //-- Imprime su jugada --
    // void imprimirMovs (vector<Movimiento>& movs);

    friend std::ostream& operator<<(std::ostream& out, const Equipo &e);
    friend std::istream& operator>>(std::istream& in, const Equipo &e);

private:
    Genoma _genoma;
    bool _enDerecha;
};

#endif
