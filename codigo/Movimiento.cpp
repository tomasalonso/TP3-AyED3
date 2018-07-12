#include "Movimiento.hpp"


std::ostream& operator<<(std::ostream& out, const Movimiento &m) {
    if (m.esPase()) {
        out << "PASE " << m._dir << " " << m._intensidad;
    } else {
        out << "MOVIMIENTO" << m._dir;
    }

     return out;
}

std::ostream& operator<<(std::ostream& out, const vector<Movimiento> &ms) {
    for (unsigned int i = 0; i < ms.size(); i++) {
        out << i << " " << ms[i] << endl;
    }

    return out;
}

// std::istream& operator>>(std::istream& in, Direccion &d) {
//     unsigned int e;

//     in >> e;

//     d = static_cast<Direccion>(e);

//     return in;
// }