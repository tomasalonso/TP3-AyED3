#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Equipo.hpp"
#include "Tablero.hpp"
#include "extras.hpp"


const vector<double> gI({
                         0.674698, 0.229843, -0.385308, -0.549404, -0.536437, 0.0313922, 0.15049, -0.471831, 0.356286, 0.629358, 0.147943, 0.485935, -0.409023, 0.491243, -0.619499, -0.290944, -0.856706, 0.0907766, -0.397971, -0.481115, -0.279178, -0.662916, 0.166036, -0.77522, 0.794856, -0.805083, 0.789458, 0.818362, -0.369601, -0.4198
});
const vector<double> gD({
                         -0.559614, -0.528275, -0.724203, -0.246853, 0.96323, 0.0485775, 0.272652, -0.25529, -0.800153, 0.23316, 0.468512, -0.409744, 0.92031, 0.492486, -0.70326, -0.440579, -0.315497, -0.271214, 0.377571, 0.902796, 0.863567, -0.947214, 0.227784, 0.438884, 0.573776, -0.356375, 0.299503, 0.562812, -0.515831, 0.856803
});


int main() {
    const int m = 5;
    const int n = 10;
    const unsigned int total = 100;

    const vector<Jugador> jI({
                              Jugador(0, Posicion(1,1), 0.152869),
                              Jugador(1, Posicion(2,2), 0.67807),
                              Jugador(2, Posicion(3,3), 0.137978)
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(6,4), 0.288556),
                              Jugador(1, Posicion(7,2), 0.429239),
                              Jugador(2, Posicion(8,3), 0.595944)
        });

    Equipo equipoI(gI, false);
    Equipo equipoD(gD, true);

    Tablero tablero(m, n, total, jI, jD);

    cout << tablero << endl;

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );

        cout << tablero;

        std::string line;
        std::getline(std::cin, line);
    }

    return 0;
}
