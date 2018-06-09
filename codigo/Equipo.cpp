#include "Equipo.hpp"

#include <cassert>


Equipo::Equipo(Genoma genoma, const vector<Jugador> jugadores,
                const unsigned int &M, const unsigned int &N,
                const unsigned int &total, bool enDerecha)
 : _tablero(M,N,total) {
    _genoma = genoma;
    _en_derecha = enDerecha;
 }

// Jugador& Equipo::jugador(size_t i) {
//     assert(i < 6);
    // if(i/3) {
    //     return _tablero._jugadoresD[i%3];
    // }
    // return _tablero._jugadoresI[i%3];
// }

bool Equipo::en_derecha() {
    return _en_derecha;
}

// void Equipo::reiniciar() {
//     for (Jugador& j : _jugadores) {
//         j.reiniciar();
//     }
// }

vector<Movimiento> Equipo::turno(vector<Movimiento> movs,
                                 function<vector<vector<Movimiento>> (void) > generarPosiblesJugadas) {
    _tablero.actualizar(movs);
    vector<Movimiento> mejorJugada;
    // generamos de manera todos los movimientos
    // (asumimos que el oponente se queda quieto)
    vector<vector<Movimiento>> jugadas = generarPosiblesJugadas();
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente

    for (auto &j : jugadas) {       // Devuelve todas válidas
        if (evaluarTablero(j)) {
            mejorJugada = j;
        }
    }
    return mejorJugada;
}

void Equipo::imprimirMovs (vector<Movimiento>& movs) {
    for (int i = 0; i < (int)movs.size(); i++) {
        if (movs[i].moverse) {
            printf("%d %s %d\n", i, "MOVIMIENTO", (int)movs[i].dir);
        } else {
            printf("%d %s %d %d\n", i, "PASE", (int)movs[i].dir, movs[i].intensidad);
        }
    }
}

vector<vector<Movimiento>> Equipo::genJugadas1() {  // Prueba TODAS las jugadas

    vector<vector<Movimiento>> jugadas;

    int filas = _tablero.M();   // esto no lo puedo acceder
    int totalDirs = 10;

    // Por cada jugada jugador 1
    for (int i = 0; i < totalDirs; ++i) {

        // Por cada jugada jugador 2
        for (int j = 0; j < totalDirs; ++j) {

            // Por cada jugada jugador 3
            for (int k = 0; k < totalDirs; ++k) {
                // Todos se mueven
                vector<Movimiento> jugada = { Movimiento((Direccion)i),
                                              Movimiento((Direccion)j),
                                              Movimiento((Direccion)k)  };

                if(esJugadaValida(jugada)) {
                    jugadas.push_back(jugada);
                }

                // Si alguno tiene la pelota, considero los posibles pases
                if(_tablero.pelotaEnPosesion() && k > 0) {

                    int idJugadorPelota = (int)(_tablero.jugadorPelota()).id();
                    if(idJugadorPelota < 4) {   // es de mi equipo

                        // Por cada posible intensidad
                        for (int inten = 0; inten < filas/2; ++inten) {
                            jugada[idJugadorPelota] = Movimiento((Direccion)k,inten);
                            if(esJugadaValida(jugada)) {
                                jugadas.push_back(jugada);
                            }
                        }
                    }
                }
            }

        }
    }
    return jugadas;
}

int Equipo::evaluarTablero(vector<Movimiento> posiblesMovs) { // evalua tablero dado posible combinacion de movs
    vector<int> mediciones(10);     // puede variar el 10
    int puntaje = 0;

    // para cada jugador mío
        vector<int> dist = _tablero.distJugadorAlArco(_en_derecha);
        mediciones[0] = dist[0];
        mediciones[1] = dist[1];
        mediciones[2] = dist[2];


    // if(_en_derecha){


    //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresD[0]);
    //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresD[1]);
    //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresD[2]);
    // } else {
    //     mediciones[0] = _tablero.distJugadorAlArco(_jugadoresI[0]);
    //     mediciones[1] = _tablero.distJugadorAlArco(_jugadoresI[1]);
    //     mediciones[2] = _tablero.distJugadorAlArco(_jugadoresI[2]);

    // }
    mediciones[3] = _tablero.distPelotaArco(_en_derecha);
    int pose = 0;
    // cercanía rival cambia si tengo o no la pelota
    if(_tablero.pelotaEnPosesion() &&
                        ((!_en_derecha && _tablero.jugadorPelota().id() < 3) ||
                         (_en_derecha && _tablero.jugadorPelota().id() >= 3)    )) {  // Tengo la pelota
        pose = _genoma.size()/2;
        // mediciones[4] = cercaniaARival(Jugador&, true);
    } else {
        pose = 0;
        // mediciones[4] = cercaniaARival(Jugador&, false);
    }

    // mediciones[5] = areaCubierta(bool _en_derecha);

    for (int i = 0 ; i < (int)_genoma.size()/2; i++) {      // asume misma longitud
        puntaje += _genoma[i+pose] * mediciones[i];
    }

    return puntaje;
}

bool Equipo::esJugadaValida(vector<Movimiento> posiblesMovs) { // evalua tablero dado posible combinacion de movs
    // me hago copia del equipo para modificarlos
    vector<Jugador> equipo = _tablero.verJugadores(_en_derecha);
    vector<Posicion> nuevasPos(3, Posicion(-1,-1));



// TO_DO: contemplar posición dentro del arco



    for (int i = 0; i < 3; i++) {
        Movimiento& movActual = posiblesMovs[i];
        int pos_x;
        int pos_y;
        int n = _tablero.N();
        int m = _tablero.M();

        // si tira la pelota tengo que chequear parámetros
        if (!movActual.moverse) {
            Posicion pelota = _tablero.posPelota();

            // restricción del enunciado
            if(movActual.intensidad > m/2) {
                return false;
            }

            // muevo la pelota (simulo movimiento)
            for(int j = 0; j < movActual.intensidad; j++) {
                pelota.mover(movActual);
                pelota.mover(movActual);  // por cada "turno" avanza dos casilleros
            }
            // coloco resultados en esas variables, voy a chequearlo mas abajo
            pos_x = pelota.x();
            pos_y = pelota.y();

        } else {

            // se mueve el jugador con o sin pelota
            equipo[i].mover(movActual);
            equipo[i].actualizar();     // les pongo la nueva dirección

            pos_x = equipo[i].pos().x();
            pos_y = equipo[i].pos().y();

            if(_tablero.pelotaEnPosesion() &&   // si alguien tiene la pelota
               _tablero.jugadorPelota().id() != equipo[i].id() && // y no soy yo
               enArco(n,m,equipo[i].pos())) {               // y entré al arco como une gile
                return false;
            }

        }


        // chequeo que la posicion final de la pelota/jugadore sea válida
        if ( !(0 <= pos_x && pos_x < n &&
                 0 <= pos_x && pos_y < m)) { // se va de cancha
            return false;
        }
    }

    // acá chequeo que no haya dos jugadores de un mismo equipo en la misma celda
    for (auto jugadorA : equipo) {
        for (auto jugadorB : equipo) {
            if (jugadorA.id() != jugadorB.id() &&
                            jugadorA.pos() == jugadorB.pos()) {
                return false;
            }
        }
    }

    return true;
}


bool enArco(int n, int m, const Posicion& pos) {
    vector<Posicion> posDeArco(6,Posicion(-1,-1));

    int mitadArco = (m/2)+1;  // celda del medio, el arco mide tres celdas

    posDeArco[0] = Posicion(-1, mitadArco +1);
    posDeArco[1] = Posicion(-1, mitadArco);
    posDeArco[2] = Posicion(-1, mitadArco -1);
    posDeArco[3] = Posicion(m, mitadArco +1);
    posDeArco[4] = Posicion(m, mitadArco);
    posDeArco[5] = Posicion(m, mitadArco -1);

    return 1 == count(posDeArco.begin(), posDeArco.end(), pos);
}