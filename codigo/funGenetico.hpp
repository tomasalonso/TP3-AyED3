#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <iostream>
// #include <map>
#include <chrono>
#include <algorithm>

#include "extras.hpp"
#include "Equipo.hpp"
#include "Tablero.hpp"
#include "GridSearch.hpp"


#ifndef FUN_GEN
#define FUN_GEN
using namespace std;
using namespace std::chrono;

typedef function<vector<int>(vector<Genoma> &poblacion, unsigned int n, unsigned int m, unsigned int total)> fun_fitness_type;

typedef function<pair<vector<Genoma>,vector<Genoma> > (vector<Genoma> &poblacion, vector<int> &puntajes, double fracc_poblacion)> fun_seleccion_type;

typedef function<void(Genoma &individuo, double proba_mutacion)> fun_mutacion_type;

typedef function<Genoma(Genoma &a, Genoma &b)> fun_crossover_type;

typedef tuple<int, int, double, int, int, int, double,
                fun_fitness_type, int, fun_seleccion_type, int,
                fun_mutacion_type, int, fun_crossover_type, int> casos_type;



Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        double proba_mutacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        double fracc_conservar,
                        fun_fitness_type fitness,
                        unsigned int f_ind,
                        fun_seleccion_type seleccion,
                        unsigned int s_ind,
                        fun_mutacion_type mutacion,
                        unsigned int m_ind,
                        fun_crossover_type crossover,
                        unsigned int c_ind                    );

vector<Genoma> poblacion_inicial(unsigned int tamanio_poblacion);

vector<int> fitness_puntos(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);
vector<int> fitness_dif_goles(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total);

pair<vector<Genoma>,vector<Genoma> > seleccion_por_puntaje(vector<Genoma> &poblacion,
                                                           vector<int> &puntajes,
                                                           double varianza);

pair<vector<Genoma>,vector<Genoma> > seleccion_por_cantidad(vector<Genoma> &poblacion,
                                                            vector<int> &puntajes,
                                                            double fracc_poblacion);

void mutacion_A(Genoma &individuo, double proba_mutacion);
void mutacion_B(Genoma &individuo, double proba_mutacion);

vector<Genoma> hacer_crossover( vector<Genoma> &poblacion,
                                fun_mutacion_type mutacion,
                                double proba_mutacion,
                                fun_crossover_type crossover,
                                unsigned int best);

Genoma crossover_BLOQUES(Genoma &a,Genoma &b);
Genoma crossover_RANDOM(Genoma &a,Genoma &b);

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total);

pair<double, double> calcular_estimadores(vector<int> muestra);

Genoma generar();

#endif
