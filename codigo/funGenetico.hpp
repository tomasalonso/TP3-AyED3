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
                        unsigned int proba_mutacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        double fracc_conservar,
                        function<vector<int>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> > (vector<Genoma> &poblacion,
                                                vector<int> &puntajes,
                                                double fracc_poblacion)> seleccion,
                        function<Genoma(Genoma &individuo, unsigned int proba_mutacion)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b, unsigned int proba_mutacion)> crossover );

vector<Genoma> poblacion_inicial(unsigned int tamanio_poblacion);

vector<int> fitness_puntos(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);
vector<int> fitness_dif_goles(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);

// pair<vector<Genoma>,vector<Genoma> > seleccion_A(vector<Genoma> &poblacion, vector<int> puntajes);
// pair<vector<Genoma>,vector<Genoma> > seleccion_B(vector<Genoma> &poblacion, vector<int> puntajes);

void mutacion_A(Genoma &individuo, unsigned int proba_mutacion);
void mutacion_B(Genoma &individuo, unsigned int proba_mutacion);

vector<Genoma> hacer_crossover( vector<Genoma> &poblacion,
                                function<Genoma(Genoma &individuo,
                                                unsigned int proba_mutacion)> mutacion,
                                unsigned int proba_mutacion,
                                function<Genoma (Genoma &a,Genoma &b, unsigned int proba_mutacion)> crossover);

Genoma crossover_BLOQUES(Genoma &a,Genoma &b, unsigned int proba_mutacion);
Genoma crossover_RANDOM(Genoma &a,Genoma &b, unsigned int proba_mutacion);

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total);

#endif
