#ifndef __EXTRAS__
#define __EXTRAS__

#include <vector>

using namespace std;

// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs);

typedef vector<double> Genoma;

enum Busqueda { LOCAL, BRUTUS, GRASP };

#define genoma_size 18
#define prob0 15
#define prob1 16
#define prob2 17

//  @TODO: arreglar los indices con el esquema difinitivo de los genomas

#define inicio_dist_j_a     0
#define fin_dist_j_a        5

#define inicio_dist_p_a     6
#define fin_dist_p_a        7

#define inicio_dist_rival   8
#define fin_dist_rival      13

#define area                14

#define inicio_probas       15
#define fin_probas          17

#endif

// GENOMA:
//    0   1   2   3   4   5       6           7       8   9  10  11   12  13       14          15  16  17
// [    |   |   |   |   |   |           |           |   |   |   |   |   |   |                |   |   |   ]
// |-con pelota-|-sin pelota|-con pelota|-sin pelota|-con pelota|-sin pelota|                |           |
// |----dist jug al arco----|---dist pelota arco----|-----cercania rival----| area cubierta  |---probas--|