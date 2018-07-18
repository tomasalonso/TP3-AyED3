#include "GridSearch.hpp"

#include <random>
#include <iostream>
#include <map>
#include <chrono>
#include <algorithm>

#include "funGenetico.hpp"

int main()
{
    for (const double g : grasp(1, 10, 5, 100)) {
      cout << g << endl;
    }

    return 0;
}

Genoma grasp(const unsigned int cantIteraciones,
           const unsigned int n, const unsigned int m,
           const unsigned int total) {

    vector<Genoma> maximos;
    Genoma mejor;
    for (unsigned int i = 0; i < cantIteraciones; i++) {
        const Genoma random = generar();
        const Genoma local = busquedaLocal(random, n, m, total);

        maximos.push_back(local);
    }

    fitness_puntos(maximos, n, m, total);

    return maximos[0];
}

Genoma generar() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generador (seed);
    std::uniform_real_distribution<double> distribucion{0.0,1.0};

    Genoma random;

    for (unsigned int j = 0; j < genoma_size; ++j) {
        const double rand_num = distribucion(generador);

        random.push_back(rand_num);
        cerr << rand_num << endl;
    }

    return random;
}

Genoma busquedaLocal(const Genoma &g, const unsigned int n,
                     const unsigned int m, const unsigned int total) {
    Genoma actual = g;
    Genoma viejo;
    do {
        viejo = actual;
        for(Genoma vecino : generar_vecinos(actual)) {

            // Los hacemo jugar
            pair<unsigned int, unsigned int> resultado = jugar(actual, vecino, n, m, total);
            if (resultado.first < resultado.second) {
                actual = vecino;
            }
        }
    } while (actual != viejo);

    return actual;
}

vector<Genoma> generar_vecinos(Genoma actual) {
  vector<Genoma> vecinos;
  for(unsigned int i = 0; i < genoma_size; i++) {
      Genoma nuevo = actual;
      nuevo[i] += 0.05;
      if(nuevo[i] > 1) {
          nuevo[i] = 1;
      }
      vecinos.push_back(nuevo);

      nuevo = actual;
      nuevo[i] -= 0.05;
      if(nuevo[i] < 0) {
          nuevo[i] = 0;
      }
      vecinos.push_back(nuevo);
  }
  return vecinos;
}

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total) {

    const vector<Jugador> jI({
                          Jugador(0, Posicion(1,1), jugA[prob0]),
                          Jugador(1, Posicion(2,2), jugA[prob1]),
                          Jugador(2, Posicion(3,3), jugA[prob2])
    });
    const vector<Jugador> jD({
                          Jugador(0, Posicion(6,1), jugB[prob0]),
                          Jugador(1, Posicion(7,2), jugB[prob1]),
                          Jugador(2, Posicion(8,3), jugB[prob2])
    });


    Equipo equipoI(jugA, false);
    Equipo equipoD(jugB, true);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );
    }

    return tablero.goles();
}
