#ifndef __MOVIMIENTO__
#define __MOVIMIENTO__

#include <cassert>
#include <ostream>
#include <vector>

using namespace std;

enum Direccion {
    QUIETO = 0,
    ARRIBA = 2,
    ABAJO = 6,
    IZQUIERDA = 8,
    DERECHA = 4,
    ARRIBA_IZQUIERDA = 1,
    ARRIBA_DERECHA = 3,
    ABAJO_IZQUIERDA = 7,
    ABAJO_DERECHA = 5
};

class Movimiento {
public:
    Movimiento() : _dir(QUIETO), _intensidad(0) {};
    Movimiento(Direccion d) : _dir(d), _intensidad(1) {};
    Movimiento(Direccion d, unsigned int i) : _dir(d), _intensidad(i) {
        assert(d != QUIETO);
    }

    bool esPase() const;

    Direccion dir() const;

    unsigned int intensidad() const;

    void bajarIntensidad(unsigned int i);

    friend std::ostream& operator<<(std::ostream& out, const Movimiento &m);

private:
    Direccion _dir;
    unsigned int _intensidad;
};

std::ostream& operator<<(std::ostream& out, const vector<Movimiento> &ms);


#endif
