#ifndef __EXTRAS__
#define __EXTRAS__

#include <vector>

using namespace std;

// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs);

typedef vector<double> Genoma;

enum Busqueda { LOCAL, BRUTUS, GRASP };

#define genoma_size 13
#define prob0 10
#define prob1 11
#define prob2 12

#endif
