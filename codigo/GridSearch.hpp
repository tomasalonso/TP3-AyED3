#ifndef _GRID_
#define _GRID_

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "extras.hpp"
#include "Equipo.hpp"
#include "Tablero.hpp"
/*
    THIS IS GRID SEARCH!!!!
    S = conjunto de soluciones
    N(s) = soluciones “vecinas”de la soluci´on s
    f(s) = valor de la soluci´on s
    elegir una soluci´on inicial s∗ ∈ S
    repetir
        elegir s ∈ N(s∗) tal que f (s) < f (s∗)
        reemplazar s∗ por s
        hasta que f (s) > f (s∗) para todos los s ∈ N(s∗)
*/

Genoma busquedaLocal(const Genoma &g, const unsigned int n,
                     const unsigned int m, const unsigned int total);

Genoma grasp(const unsigned int cantIteraciones,
             const unsigned int n, const unsigned int m,
             const unsigned int total);

Genoma generar();

vector<Genoma> generar_vecinos(Genoma actual);

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total);

#endif
