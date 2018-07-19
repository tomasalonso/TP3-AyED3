#ifndef __EXTRAS__
#define __EXTRAS__

#include <vector>

using namespace std;

// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs);

typedef vector<double> Genoma;

#define genoma_size 30
#define prob0 28
#define prob1 17
#define prob2 29

//  @TODO: arreglar los indices con el esquema difinitivo de los genomas

#define inicio_dist_j_a         0
#define fin_dist_j_a            5

#define inicio_dist_p_a         6
#define fin_dist_p_a            7

#define inicio_dist_rival       8
#define fin_dist_rival          13

#define inicio_dist_j_p         14
#define fin_dist_j_p            19

#define inicio_dist_j_lateral   20
#define fin_dist_j_lateral      25

#define area                    26

#define inicio_probas           27
#define fin_probas              29

#endif

// GENOMA:

//    0   1   2   3   4   5       6           7       8   9  10  11   12  13  14  15  16  17  18  19  20  21  22  23  24 25     26    27  28  29
// [    |   |   |   |   |   |           |           |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   ]
// |-con pelota-|-sin pelota|-con pelota|-sin pelota|-con pelota|-sin pelota|-con pelota|-sin pelota|-con pelota|-sin pelota|       |           |
// |----dist jug al arco----|---dist pelota arco----|-----cercania rival----|---cercania a pelota---|---cercania a lateral--| area  |---probas--|
