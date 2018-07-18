#ifndef __EXTRAS__
#define __EXTRAS__

#include <vector>

using namespace std;

// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs);

typedef vector<double> Genoma;

enum Busqueda { LOCAL, BRUTUS, GRASP };

#define genoma_size 17
#define prob0 14
#define prob1 15
#define prob2 16

//  @TODO: arreglar los indices con el esquema difinitivo de los genomas

#define inicio_ataque   0
#define fin_ataque      5
#define inicio_defensa  6
#define fin_defensa     13
#define inicio_proba    14
#define fin_proba       16

#endif
//    0   1   2   3   4   5       6           7       8   9  10  11   12  13  14  15  16
// [    |   |   |   |   |   |           |           |   |   |   |   |   |   |   |   |   ]
// |-con pelota-|-sin pelota|-con pelota|-sin pelota|-con pelota|-sin pelota|
// |----dist jug al arco----|---dist pelota arco----|-----cercania rival----|---probas--|