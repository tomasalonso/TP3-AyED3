#include "funGenetico.hpp"
#include <random>
#include <iostream>
#include <chrono>


int main()
{
    // auto poblacion = poblacion_inicial(2);
    // fitness_puntos(poblacion,10,5, 5);
    return 0;
}
Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        unsigned int proba_mutacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        function<vector<int>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> >(vector<Genoma> &poblacion, vector<int> &puntajes)> seleccion,
                        function<Genoma(Genoma &individuo, unsigned int proba_mutacion)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b)> crossover ) {

    vector<Genoma> generacion = poblacion_inicial(tamanio_poblacion);
    vector<Genoma> generacion_siguiente = generacion;

    for (auto i = 1; i < generaciones; ++i) {
        generacion = generacion_siguiente;

        vector<int> puntajes = fitness(generacion); // me ordena ambas puntajes y generación de mayor a menor puntaje

        pair<vector<Genoma>,vector<Genoma> > divididos = seleccion(generacion, puntajes);

        vector<Genoma> cruzados = hacer_crossover(divididos.second, mutacion, proba_mutacion);

        generacion_siguiente = divididos.first;

        generacion_siguiente.insert(generacion_siguiente.end(), cruzados.begin(), cruzados.end());
    }

    return generacion[0];
}

vector<Genoma> poblacion_inicial(unsigned int tamanio_poblacion) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);


    // std::default_random_engine _generador;
    std::uniform_real_distribution<double> _distribucion{0.0,1.0};

    vector<Genoma> poblacion;

    for (int i = 0; i < tamanio_poblacion; ++i) {
        Genoma actual;
        for (int j = 0; j < genoma_size; ++j) {
            double rand_num = _distribucion(_generador);
            actual.push_back(rand_num);
            cout<<rand_num<<endl;
        }
        poblacion.push_back(actual);
    }
    return poblacion;
}

vector<int> fitness_puntos(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total){
// CONTEMPLA EMPATES
    vector<int> puntos(poblacion.size(), 0);

    for (unsigned int i = 0; i < poblacion.size(); i++) {
        for (unsigned int j = i + 1; j < poblacion.size(); j++) {

            pair<unsigned int, unsigned int> goles = jugar(poblacion[i],poblacion[j],n, m, total);

            // PUNTUAR
            if (goles.first > goles.second ) {
                puntos[i]+= 3;
            } else if (goles.first < goles.second) {
                puntos[j]+= 3;
            } else {
                puntos[i]+= 1;
                puntos[j]+= 1;
            }
            cout<< puntos[i]<<" , "<<puntos[j]<<endl;
        }
    }

    return puntos;
}
vector<int> fitness_dif_goles(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total){

// NO CONTEMPLA EMPATES. Si gana le doy un punto más.
    vector<int> dif_goles(poblacion.size(), 0);

    for (unsigned int i = 0; i < poblacion.size(); i++) {
        for (unsigned int j = i; j < poblacion.size(); ++j) {
            pair<unsigned int, unsigned int> goles = jugar(poblacion[i],poblacion[j],n, m, total);

            // PUNTUAR
            if (goles.first > goles.second ) {
                dif_goles[i]++;
            } else if (goles.first < goles.second) {
                dif_goles[j]++;
            }

            dif_goles[i] += (goles.first-goles.second); // mis goles menos los del oponente
            dif_goles[j] += (goles.second-goles.first);
        }
    }

    return dif_goles;
}

pair<vector<Genoma>,vector<Genoma> > seleccion_A(vector<Genoma> &poblacion, vector<int> &puntajes){
    std::vector<Genoma> v;
    return make_pair(v,v);
}
pair<vector<Genoma>,vector<Genoma> > seleccion_B(vector<Genoma> &poblacion, vector<int> &puntajes){
    std::vector<Genoma> v;
    return make_pair(v,v);
}

void mutacion_A(Genoma &individuo, unsigned int proba_mutacion){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_real_distribution<double> _dist_continua{0.0,1.0};
    std::uniform_int_distribution<int> _dist_discreta{0,genoma_size-1};

    double muto = _dist_continua(_generador);

    if (muto <= proba_mutacion) {
        int indice_random = _dist_discreta(_generador);
        individuo[indice_random] = _dist_continua(_generador);
    }
}

void mutacion_B(Genoma &individuo, unsigned int proba_mutacion){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_real_distribution<double> _dist_continua{0.0,1.0};
    std::uniform_int_distribution<int> _dist_discreta{0,genoma_size-1};

    double muto = _dist_continua(_generador);

    if (muto <= proba_mutacion) {
        int indice_random = _dist_discreta(_generador);
        individuo[indice_random] = 1-individuo[indice_random];
    }

}

vector<Genoma> hacer_crossover( vector<Genoma> &poblacion,
                                function<Genoma(Genoma &individuo,
                                                unsigned int proba_mutacion)> mutacion,
                                unsigned int proba_mutacion){
    vector<Genoma> v;
    return v;
}

Genoma crossover_A(Genoma &a,Genoma &b){
    vector<double> v;
    return v;
}
Genoma crossover_B(Genoma &a,Genoma &b){
    vector<double> v;
    return v;}

pair<unsigned int, unsigned int> jugar(Genoma &jugA, Genoma &jugB, int n, int m, int total) {

    const vector<Jugador> jI({
                          Jugador(0, Posicion(1,1), jugA[prob0]),
                          Jugador(1, Posicion(2,2), jugA[prob1]),
                          Jugador(2, Posicion(3,3), jugA[prob2])
    });
    const vector<Jugador> jD({
                          Jugador(0, Posicion(6,1), jugB[prob0]),
                          Jugador(1, Posicion(7,2), jugB[prob1]),
                          Jugador(2, Posicion(8,3), jugB[prob2])
    });


    Equipo equipoI(jugA, false);
    Equipo equipoD(jugB, true);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );
        cout << tablero;
    }

    return tablero.goles();
}