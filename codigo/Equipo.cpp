#include "Equipo.hpp"

#include <cassert>


Equipo::Equipo(Genoma genoma, const vector<Jugador> misJugadores,
                const vector<Jugador> otrosJugadores,
                const unsigned int &M, const unsigned int &N,
                const unsigned int &total, bool enDerecha)
 : _tablero(M,N,total, misJugadores, otrosJugadores) {
    _genoma = genoma;
    _en_derecha = enDerecha;
 }

const Jugador& Equipo::jugador(size_t i) const {
    assert(i < 6);
    if(i/3) {
        return _tablero.verJugadores(false)[i%3];
    }

    return _tablero.verJugadores(true)[i%3];
}

bool Equipo::en_derecha() {
    return _en_derecha;
}

// void Equipo::reiniciar(bool metiGol) {
// }

vector<Movimiento> Equipo::turno(vector<Movimiento> movs,
                                 function<vector<vector<Movimiento>> (void) > generarPosiblesJugadas) {
    _tablero.actualizar(movs, _en_derecha);
    vector<Movimiento> mejorJugada;
    // generamos de manera todos los movimientos
    // (asumimos que el oponente se queda quieto)
    vector<vector<Movimiento>> jugadas = generarPosiblesJugadas();
    // @TO-DO: algo que pruebe menos jugadas de manera inteligente
    int puntajeMejor = -1;
    int puntajeActual;
    for (auto &j : jugadas) {  // Devuelve todas válidas
        puntajeActual = evaluarTablero(j);
        if(puntajeActual > puntajeMejor) {
            puntajeMejor = puntajeActual;
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

    int filas = _tablero.M();
    int totalDirs = 9;

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
                if(_tablero.pelotaEnPosesion()) {

                    int idJugadorPelota = (int)(_tablero.jugadorPelota()).id();
                    if(idJugadorPelota < 4) {   // es de mi equipo

                        // Por cada posible direccion
                        for (int dir = 1; dir < 9; ++dir) {

                            // Pongo esto para no probar más intensidades de las necesarias en una misma dirección
                            bool intensidadTope = false;
                            // Por cada posible intensidad
                            for (int inten = 0; inten < filas/2 && !intensidadTope ; ++inten) {

                                jugada[idJugadorPelota] = Movimiento((Direccion)dir, inten);
                                if(esJugadaValida(jugada)) {
                                    jugadas.push_back(jugada);
                                } else {
                                    intensidadTope = true;
                                }
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
        vector<unsigned int> dist = _tablero.distJugadorAlArco(_en_derecha);
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
    // Si tengo la pelota
    if(_tablero.pelotaEnPosesion() &&
                        ((!_en_derecha && _tablero.jugadorPelota().id() < 3) ||
                         (_en_derecha && _tablero.jugadorPelota().id() >= 3)    )) {
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
    // me hago copia del equipo para modificarlos y ver como quedan las posiciones
    vector<Jugador> equipo = _tablero.verJugadores(_en_derecha);
    vector<Posicion> nuevasPos(3, Posicion(-1,-1));
    int n = _tablero.N();
    int m = _tablero.M();

   for (int i = 0; i < 3; i++) {
        Movimiento& movActual = posiblesMovs[i];
        int pos_x;
        int pos_y;

        if (movActual.moverse) {

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

        } else {

            // si tira la pelota tengo que chequear parámetros

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
        }


        // chequeo que la posicion final de la pelota/jugadore sea válida
        // se va de cancha y no está en el arco
        if ( !(0 <= pos_x && pos_x < n && 0 <= pos_x && pos_y < m) &&
                                !enArco(n, m, Posicion(pos_x, pos_y))) {
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

    int mitadArco = (m/2);  // celda del medio, el arco mide tres celdas

    posDeArco[0] = Posicion(-1, mitadArco +1);
    posDeArco[1] = Posicion(-1, mitadArco);
    posDeArco[2] = Posicion(-1, mitadArco -1);
    posDeArco[3] = Posicion(n, mitadArco +1);
    posDeArco[4] = Posicion(n, mitadArco);
    posDeArco[5] = Posicion(n, mitadArco -1);

    return 1 == count(posDeArco.begin(), posDeArco.end(), pos);
}


vector<tuple<int, int, int, string> > leerEstadoArbitro(iostream& in) {
    vector<tuple<int, int, int, string> > estados (6);
    bool leerPelota = true;
    int id, fila, col;
    string posesion;
    for (int i = 0; i < 6; ++i) {

        in >> id >> fila >> col >> posesion;
        estados[i] = make_tuple(id, fila, col, posesion);

        leerPelota = leerPelota && (posesion == "SIN_PELOTA");
    }
    if (leerPelota) {
        in >> fila >> col;
        estados[6] = make_tuple(-1, fila, col, "pelota");
    }
    return estados;
}
