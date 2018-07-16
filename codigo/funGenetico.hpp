#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "extras.hpp"
#include "Equipo.hpp"
#include "Tablero.hpp"


#ifndef FUN_GEN
#define FUN_GEN
using namespace std;


Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        function<vector<int>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> >(vector<Genoma> &poblacion, vector<int> &puntajes)> seleccion,
                        function<Genoma(Genoma &individuo)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b)> crossover );

vector<Genoma> poblacion_inicial(unsigned int tamanio_poblacion);

vector<int> fitness_puntos(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);
vector<int> fitness_dif_goles(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);

pair<vector<Genoma>,vector<Genoma> > seleccion_A(vector<Genoma> &poblacion, vector<int> puntajes);
pair<vector<Genoma>,vector<Genoma> > seleccion_B(vector<Genoma> &poblacion, vector<int> puntajes);

Genoma mutacion_A(Genoma &individuo);
Genoma mutacion_B(Genoma &individuo);

vector<Genoma> hacer_crossover(vector<Genoma> &poblacion, function<Genoma(Genoma &individuo)> mutacion);

Genoma crossover_A(Genoma &a,Genoma &b);
Genoma crossover_B(Genoma &a,Genoma &b);

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total);

#endif
