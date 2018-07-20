#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Equipo.hpp"
#include "Tablero.hpp"
#include "extras.hpp"


const vector<double> gI({
// crossover RANDOM
-0.589364, 0.652226, -0.507876, 0.388526, -0.344394, -0.203026, 0.493318, 0.505395, 0.986491, -0.0153749, -0.214718, -0.295698, -0.882941, 0.206117, 0.0142715, 0.810046, 0.0971497, -0.371663, 0.664317, -0.0883049, -0.757279, -0.799241, -0.26386, 0.710006, 0.599131, -0.223488, -0.319659, 0.203676, 0.922115, 0.660334

// fitness PUNTAJE
// -0.0912428, 0.441283, 0.526057, -0.24552, -0.495963, -0.44873, -0.994717, -0.158943, 0.652438, 0.664869, 0.230037, 0.374349, -0.995683, 0.800342, -0.515715, 0.741213, 0.356681, 0.0936855, -0.615283, -0.43112, 0.101387, 0.222677, -0.500011, 0.0475549, -0.874837, 0.190928, -0.818234, 0.50323, 0.514024, 0.230156

// seleccion por CANTIDAD
// -0.0994216, 0.882552, 0.902672, 0.822181, -0.699707, 0.514584, -0.88109, 0.0527105, -0.554145, 0.773321, 0.586765, 0.588974, -0.829386, -0.833506, -0.0828857, 0.136037, 0.442752, 0.0283666, -0.000342209, 0.326409, -0.591783, -0.703476, -0.795474, -0.970976, -0.564937, 0.285668, -0.358286, 0.600258, 0.768972, 0.659929

// mutacion A (random)
// -0.602419, 0.772077, 0.635428, -0.646348, -0.647208, 0.332115, -0.644658, -0.688586, 0.680104, 0.142376, 0.977245, -0.837937, -0.935878, 0.481869, -0.777179, 0.715096, 0.874099, 0.3127, -0.645272, -0.787528, 0.918279, 0.0649478, -0.366756, 0.486087, -0.591402, 0.802008, -0.263286, 0.196476, 0.339259, 0.844998

});
const vector<double> gD({
// crossover BLOQUES
0.0637883, -0.61614, 0.649995, -0.220379, -0.635748, -0.697865, 0.16051, 0.293574, -0.406392, 0.838909, 0.18956, -0.46366, 0.703988, -0.998117, -0.0996017, -0.200106, 0.971754, -0.388111, 0.663797, 0.469709, -0.0635755, 0.700699, -0.953205, 0.758123, 0.600004, 0.698239, 0.315688, 0.843778, 0.411682, 0.368018


//  fitness DIF_GOLES
// 0.0354922, -0.347757, -0.00128968, -0.454219, -0.352621, -0.698883, -0.959573, -0.730346, -0.451026, -0.855564, -0.898217, 0.594382, -0.377874, -0.126251, -0.297974, 0.196175, 0.964436, -0.592206, -0.578612, 0.277421, -0.015946, -0.471911, -0.019213, -0.182925, -0.847654, -0.218569, 0.730436, 0.622654, 0.912127, 0.818418

// seleccion por PUNTAJE
// 0.338534, 0.556814, -0.629017, -0.728201, 0.491463, -0.39079, -0.216044, 0.332776, -0.0646357, 0.152405, 0.982521, -0.347799, -0.969728, -0.470829, -0.0262192, 0.614969, 0.0953578, -0.272102, -0.798845, 0.457632, 0.438058, -0.780896, 0.580502, -0.845736, -0.639841, -0.0234984, -0.155304, 0.178335, 0.992425, 0.307313

// mutacion B (opuesto)
// -0.545647, 0.947161, 0.470623, -0.268744, 0.797187, 0.591215, 0.637039, -0.980517, 0.970684, 0.586548, 0.227134, -0.586512, -0.171926, -0.222206, -0.758129, 0.375217, 0.0363852, -0.382173, 0.258794, -0.49472, -0.712859, 0.87179, -0.0760118, 0.615695, 0.290044, -0.249712, -0.831808, 0.405928, 0.672154, 0.205472

});


int main() {
    const int m = 5;
    const int n = 10;
    const unsigned int total = 70;

    const vector<Jugador> jI({
                              Jugador(0, Posicion(4,2), gI[prob0]),
                              Jugador(1, Posicion(1,1), gI[prob1]),
                              Jugador(2, Posicion(1,3), gI[prob2])
        });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(5,2), gD[prob0]),
                              Jugador(1, Posicion(8,1), gD[prob1]),
                              Jugador(2, Posicion(8,3), gD[prob2])
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
