struct Posicion {
    int fila;
    int col;
} Pos;

struct Jugador {
    int id;
    Pos p;
    Pos inicial;
    int prob_quite;
    // bool pelota;
};

struct Pelota {
    Pos p;
    int tiempo_mov;
};

struct Equipo {
    Jugador j1;
    Jugador j2;
    Jugador j3;
    bool en_derecha;
    // Pos inicial: Array de 3 tuplas
};

struct Tablero {
    int filas;
    int cols;
    int tiempo;
    Pelota pelota;

    int id_eq_pelota;   // estos me dicen qué equipo y jugador tiene la pelota
    int id_j_pelota;

    Equipo eq_der;
    int goles_der;

    Equipo eq_izq;
    int goles_izq;
};

