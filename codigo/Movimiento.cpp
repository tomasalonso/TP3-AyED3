#include "Movimiento.hpp"


bool Movimiento::esPase() const {
     return (_intensidad > 1);
 }

Direccion Movimiento::dir() const {
    return _dir;
}

unsigned int Movimiento::intensidad() const {
    return _intensidad;
}

void Movimiento::bajarIntensidad(unsigned int i) {
    _intensidad -= i;
}


std::ostream& operator<<(std::ostream& out, const Movimiento &m) {
    if (m.esPase()) {
        out << "PASE " << m._dir << " " << (m._intensidad/2);
    } else {
        out << "MOVIMIENTO " << m._dir;
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
