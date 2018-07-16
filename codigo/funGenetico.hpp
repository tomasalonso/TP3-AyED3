#include "extras.hpp"
Genoma hacer_genetico(unsigned int generaciones);
vector<Genoma> poblacion_inicial();
double fitness_goles(vector<Genoma> &poblacion);
double fitness_dif_goles(vector<Genoma> &poblacion);
vector<Genoma> seleccion_A(vector<Genoma> &poblacion);
vector<Genoma> seleccion_B(vector<Genoma> &poblacion);

Genoma mutacion_A(Genoma &individuo);
Genoma mutacion_B(Genoma &individuo);