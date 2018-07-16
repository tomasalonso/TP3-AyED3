#include "extras.hpp"
#include <functional>
#ifndef FUN_GEN
#define FUN_GEN
using namespace std;


Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        function<vector<double>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> >(vector<Genoma> &poblacion, vector<double> &puntajes)> seleccion,
                        function<Genoma(Genoma &individuo)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b)> crossover );

vector<Genoma> poblacion_inicial(unsigned int tamanio_poblacion);

vector<double> fitness_goles(vector<Genoma> &poblacion);
vector<double> fitness_dif_goles(vector<Genoma> &poblacion);

pair<vector<Genoma>,vector<Genoma> > seleccion_A(vector<Genoma> &poblacion, vector<double> puntajes);
pair<vector<Genoma>,vector<Genoma> > seleccion_B(vector<Genoma> &poblacion, vector<double> puntajes);

Genoma mutacion_A(Genoma &individuo);
Genoma mutacion_B(Genoma &individuo);

vector<Genoma> hacer_crossover(vector<Genoma> &poblacion, function<Genoma(Genoma &individuo)> mutacion);

Genoma crossover_A(Genoma &a,Genoma &b);
Genoma crossover_B(Genoma &a,Genoma &b);

void jugar(Genoma a, Genoma b);

#endif
