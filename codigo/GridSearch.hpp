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
#ifndef GRID
#define GRID

Genoma hacer_grid(unsigned int n, unsigned int m, unsigned int total);

vector<Genoma> generar_vecinos(Genoma actual);

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total);

#endif 