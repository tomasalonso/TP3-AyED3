#include "GridSearch.hpp"

#include <random>
#include <iostream>
#include <map>
#include <chrono>
#include <algorithm>

#include "funGenetico.hpp"

int main()
{

    Genoma mejor = grasp(50, 10, 5, 50);
    cout << " El mejor es: " << endl;
    for (const double g : mejor) {
      cout << g << ", ";
    }
  
    cout << endl;

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
        cout << " el de la busqueda " << i << ": " << endl;
        for(double d : local) {cout << d << ", ";}
        cout << endl;
        maximos.push_back(local);
    }

    fitness_puntos(maximos, n, m, total);

    return maximos[0];
}

Genoma generar() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generador (seed);
    std::uniform_real_distribution<double> distribucion1{-1.0, 1.0};
    std::uniform_real_distribution<double> distribucion2{0, 1.0};

    Genoma random;

    for (unsigned int j = 0; j < inicio_probas; ++j) {
        const double rand_num = distribucion1(generador);

        random.push_back(rand_num);
        // cerr << rand_num << endl;
    }
    for (unsigned int j = inicio_probas; j < genoma_size; ++j) {
        const double rand_num = distribucion2(generador);

        random.push_back(rand_num);
        // cerr << rand_num << endl;
    }

    return random;
}

Genoma busquedaLocal(const Genoma &g, const unsigned int n,
                     const unsigned int m, const unsigned int total) {
    Genoma actual = g;
    Genoma viejo = g;
    Genoma anterior = g;
    do {
        anterior = viejo;
        viejo = actual;
        for(Genoma vecino : generar_vecinos(actual, anterior)) {

            // Los hacemo jugar
            pair<unsigned int, unsigned int> resultado = jugar(actual, vecino, n, m, total);
            if (resultado.first < resultado.second) {
                actual = vecino;
            }
        }
    } while (actual != viejo);

    return actual;
}

vector<Genoma> generar_vecinos(Genoma actual, Genoma anterior) {
  vector<Genoma> vecinos;
  for(unsigned int i = 0; i < inicio_probas; i++) {
      Genoma nuevo = actual;
      nuevo[i] += 0.1;
      if(nuevo[i] > 1) {
          nuevo[i] = 1;
      }
      if (nuevo != anterior) {
          vecinos.push_back(nuevo);
      }

      nuevo = actual;
      nuevo[i] -= 0.1;
      if(nuevo[i] < -1) {
          nuevo[i] = -1;
      }
      if (nuevo != anterior) {
          vecinos.push_back(nuevo);
      }
  }
  for(unsigned int i = inicio_probas; i < genoma_size; i++) {
      Genoma nuevo = actual;
      nuevo[i] += 0.1;
      if(nuevo[i] > 1) {
          nuevo[i] = 1;
      }
      if (nuevo != anterior) {
          vecinos.push_back(nuevo);
      }

      nuevo = actual;
      nuevo[i] -= 0.1;
      if(nuevo[i] < 0) {
          nuevo[i] = 0;
      }
      if (nuevo != anterior) {
          vecinos.push_back(nuevo);
      }
  }

  return vecinos;
}

vector<int> fitness_puntos(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total){
// CONTEMPLA EMPATES
    vector<int> puntos(poblacion.size(), 0);

    for (unsigned int i = 0; i < poblacion.size(); i++) {
        for (unsigned int j = i + 1; j < poblacion.size(); j++) {
            // cerr<<"Juegan i: "<<i<<" vs. j: "<<j<<endl;
            pair<unsigned int, unsigned int> goles = jugar(poblacion[i],poblacion[j],n, m, total);

            // PUNTUAR
            if (goles.first > goles.second ) {
                puntos[i]+= 3;
            } else if (goles.first < goles.second) {
                puntos[j]+= 3;
            } else {
                puntos[i]+= 1;
                puntos[j]+= 1;
            }
        }
    }

    // ADEMÁS TENGO QUE ORDENAR LOS PUNTAJES Y GENOMAS PARA QUE ESTÉN DE MAYOR A MENOR FITNESS
    vector<tuple<int, Genoma> > todos_juntos;
    for (unsigned int i = 0; i < poblacion.size(); i++) {
        todos_juntos.push_back(make_tuple(puntos[i],poblacion[i]));
    }

    stable_sort (todos_juntos.rbegin(), todos_juntos.rend());

    int k = 0;

    for (auto e : todos_juntos) {
        puntos[k] = get<0>(e);
        poblacion[k] = get<1>(e);
        k++;
    }

    return puntos;
}

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total) {

    const vector<Jugador> jI({
                              Jugador(0, Posicion(4,2), jugA[prob0]),
                              Jugador(1, Posicion(1,1), jugA[prob1]),
                              Jugador(2, Posicion(1,3), jugA[prob2])
    });
    const vector<Jugador> jD({
                              Jugador(0, Posicion(5,2), jugB[prob0]),
                              Jugador(1, Posicion(8,1), jugB[prob1]),
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
