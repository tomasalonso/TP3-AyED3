#include "funGenetico.hpp"
#include <random>
#include <iostream>
#include <chrono>


int main()
{
    // poblacion_inicial(1);
    return 0;
}
Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        function<vector<double>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> >(vector<Genoma> &poblacion, vector<double> &puntajes)> seleccion,
                        function<Genoma(Genoma &individuo)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b)> crossover ) {

    vector<Genoma> generacion = poblacion_inicial(tamanio_poblacion);
    vector<Genoma> generacion_siguiente = generacion;

    for (auto i = 1; i < generaciones; ++i) {
        generacion = generacion_siguiente;

        vector<double> puntajes = fitness(generacion); // me ordena ambas puntajes y generación de mayor a menor puntaje

        pair<vector<Genoma>,vector<Genoma> > divididos = seleccion(generacion, puntajes);

        vector<Genoma> cruzados = hacer_crossover(divididos.second, mutacion);

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
            // cout<<rand_num<<endl;
        }
        poblacion.push_back(actual);
    }
    return poblacion;
}

vector<double> fitness_goles(vector<Genoma> &poblacion){
    vector<double> jugados(poblacion.size());
    vector<double> goles(poblacion.size());
    vector<double> ganados(poblacion.size());

    for (auto i = 0; i < poblacion.size(); i++) {
        for (int j = i; j < count; ++j) {
            jugar(poblacion[i],poblacion[j]);
        }
    }

    return v;
}
vector<double> fitness_dif_goles(vector<Genoma> &poblacion){
        vector<double> v;
    return v;
}

pair<vector<Genoma>,vector<Genoma> > seleccion_A(vector<Genoma> &poblacion, vector<double> &puntajes){
    std::vector<Genoma> v;
    return make_pair(v,v);
}
pair<vector<Genoma>,vector<Genoma> > seleccion_B(vector<Genoma> &poblacion, vector<double> &puntajes){
    std::vector<Genoma> v;
    return make_pair(v,v);
}

Genoma mutacion_A(Genoma &individuo){
    vector<double> v;
    return v;
}
Genoma mutacion_B(Genoma &individuo){
        vector<double> v;
    return v;
}

vector<Genoma> hacer_crossover(vector<Genoma> &poblacion, function<Genoma(Genoma &individuo)> mutacion){
    vector<Genoma> v;
    return v;
}

Genoma crossover_A(Genoma &a,Genoma &b){
        vector<double> v;
    return v;
}
Genoma crossover_B(Genoma &a,Genoma &b){    vector<double> v;
    return v;}

void jugar(Genoma gI, Genoma gD, int n, int m, int total) {


    const vector<Jugador> jI({
                          Jugador(0, Posicion(1,1), gI[prob0]),
                          Jugador(1, Posicion(2,2), gI[prob1]),
                          Jugador(2, Posicion(3,3), gI[prob2])
    });
    const vector<Jugador> jD({
                          Jugador(0, Posicion(6,1), gD[prob0]),
                          Jugador(1, Posicion(7,2), gD[prob1]),
                          Jugador(2, Posicion(8,3), gD[prob2])
    });


    Equipo equipoI(gI, false);
    Equipo equipoD(gD, true);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );
        cout << tablero;
    }
}