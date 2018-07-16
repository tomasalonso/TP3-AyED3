#include "Equipo.hpp"

#include <cassert>

Equipo::Equipo(Genoma genoma, bool enDerecha) : _genoma(genoma), _enDerecha(enDerecha) {}


bool Equipo::enDerecha() {
    return _enDerecha;
}


// actualiza tablero, prueba jugadas y devuelve la mejor
vector<Movimiento> Equipo::turno(Tablero &t, const enum Busqueda opc) {
    vector<Movimiento> mejorJugada;
    
    switch(opc) {
        case LOCAL:
            mejorJugada = busquedaLocal(t);
            break;
        case BRUTUS:
            mejorJugada = fuerzaBruta(t);
            break;
        case GRASP:
            mejorJugada = grasp(t);
            break;
    }

    return mejorJugada;
}


// Genera TODAS las jugadas posibles
void Equipo::genJugadas1(Tablero &t,
                         vector<vector<Movimiento> > &jugadasPropias,
                         vector<vector<Movimiento> > &jugadasContrario) {
    vector<vector<Movimiento> > movValidosPropios;
    vector<vector<Movimiento> > movValidosContrario;

    jugadasPropias.clear();
    jugadasContrario.clear();

    if (_enDerecha) {
        t.jugadasValidas(movValidosContrario, movValidosPropios);
    } else {
        t.jugadasValidas(movValidosPropios, movValidosContrario);
    }

    jugadasContrario.push_back(vector<Movimiento>(
                                                  {Movimiento(QUIETO),
                                                   Movimiento(QUIETO),
                                                   Movimiento(QUIETO)}
                                                  ));

    // combinar([[1,2,3],[4,5,6]]) = [1,4], [1,5], [1,6], [2, 4], ...
    jugadasPropias = combinar(movValidosPropios);
}
/*
    THIS IS GRID SEARCH!!!!
    S = conjunto de soluciones
    N(s) = soluciones “vecinas”de la soluci´on s
    f(s) = valor de la soluci´on s
    elegir una soluci´on inicial s∗ ∈ S
    repetir
        elegir s ∈ N(s∗) tal que f (s) < f (s∗)
        reemplazar s∗ por s
        hasta que f (s) > f (s∗) para todos los s ∈ N(s∗)
*/

vector<Movimiento> Equipo::fuerzaBruta(Tablero &t) {
    vector<Movimiento> mejorJugada;
    vector<vector<Movimiento> > jugadasPropias;
    vector<vector<Movimiento> > jugadasContrario;

    genJugadas1(t, jugadasPropias, jugadasContrario);
    // generamos todos los movimientos
    // (asumimos que el oponente se queda quieto)
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente
    int puntajeMejor = -1;
    for (const auto &jPropia : jugadasPropias) {  // Devuelve todas válidas
        for (const auto &jContrario : jugadasContrario) {
            t.mover(jPropia, jContrario);

            const int puntajeActual = t.puntaje(_genoma, _enDerecha);

            if (puntajeActual > puntajeMejor) {
                puntajeMejor = puntajeActual;
                mejorJugada = jPropia;
            }
        }
    }

    return mejorJugada;
}

vector<Movimiento> Equipo::busquedaLocal(Tablero &t) {
    vector<Movimiento> mejorJugada;
    vector<vector<Movimiento> > jugadasPropias;
    vector<vector<Movimiento> > jugadasContrario;
    vector<vector<Movimiento> > vecindad;

    genJugadas1(t, jugadasPropias, jugadasContrario);

    const unsigned int index = std::rand() % jugadasPropias.size();
    mejorJugada = jugadasPropias[index];
    t.mover(mejorJugada, jugadasContrario[0]);
    unsigned int mejorPuntaje = t.puntaje(_genoma, _enDerecha);
    unsigned int puntajeActual;

    do {
        puntajeActual = mejorPuntaje;
        
        for(auto &vecino : vecinos(mejorJugada, jugadasPropias)) {
            t.mover(vecino, jugadasContrario[0]);
            const unsigned int puntajeVecino = t.puntaje(_genoma, _enDerecha);
            
            if(puntajeVecino > mejorPuntaje) {
                mejorJugada = vecino;
                mejorPuntaje = puntajeVecino;
            }
        }
    } while(mejorPuntaje != puntajeActual);
    return mejorJugada;
}


vector<vector<Movimiento> > Equipo::vecinos(vector<Movimiento> actual, vector<vector<Movimiento> > jugadasValidas) {

    vector<vector<Movimiento> > vecindad;
    vector<Movimiento> nuevo;
    for(unsigned int i = 0; i < jugadasValidas.size(); i++) {
        for(unsigned int j = 0; jugadasValidas[i].size(); j++) {
            nuevo = actual;
            nuevo[i] = jugadasValidas[i][j];
            vecindad.push_back(nuevo);
        }
    }
    return vecindad;
}



vector<Movimiento> Equipo::grasp(Tablero &t) {
    vector<Movimiento> mejorJugada;
    vector<vector<Movimiento> > jugadasPropias;
    vector<vector<Movimiento> > jugadasContrario;

    genJugadas1(t, jugadasPropias, jugadasContrario);

    return mejorJugada;
}






















