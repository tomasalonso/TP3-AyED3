#include "extras.hpp"

#include "Movimiento.hpp"

// Combinaciones posibles de vector de vectores
template<typename T>
vector<vector<T> > combinar(vector<vector<T> > &vs) {
    if (vs.empty()) {
        return vector<vector<T> >();
    }

    vector<vector<T> > res;

    const vector<T> back = vs.back();
    vs.pop_back();

    for (const T& m : back) {
        vector<vector<T> > comb =  combinar(vs);
        for (auto elems : comb) {
            elems.push_back(m);
        }
        res.insert(res.end(), comb.begin(), comb.end());
    }

    return res;
}

template vector<vector<Movimiento> > combinar<Movimiento>(vector<vector<Movimiento> > &vs);
