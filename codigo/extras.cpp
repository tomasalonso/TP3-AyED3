#include "extras.hpp"

#include "Movimiento.hpp"

#include <iostream>
// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs) {
    vector<vector<T> > res;

    if (vs.empty()) {
        return res;
    }
    if (vs.size() == 1) {
        res.resize(vs[0].size());
        for (unsigned int i = 0; i < vs[0].size(); i++) {
            res[i].push_back(vs[0][i]);
        }

        return res;
    }


    const vector<T> back = vs.back();
    vs.pop_back();

    vector<vector<T> > comb =  combinar(vs);
    for (const T& m : back) {
        vector<vector<T> > ccomb = comb;
        for (vector<T>& elems : ccomb) {
            elems.push_back(m);
        }
        res.insert(res.end(), ccomb.begin(), ccomb.end());
    }

    return res;
}

template vector<vector<Movimiento> > combinar<Movimiento>(vector<vector<Movimiento> > &vs);

template vector<vector<int> > combinar<int>(vector<vector<int> > &vs);
