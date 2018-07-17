#include "funGenetico.hpp"
#include <random>
#include <iostream>
#include <map>
#include <chrono>
#include <algorithm>


int main()
{
    auto poblacion = poblacion_inicial(2);
    Genoma copia = poblacion[0];
    for (auto e: poblacion[0]) {cerr<<e<<"  ";} cerr<<endl;
    for (auto e: poblacion[1]) {cerr<<e<<"  ";} cerr<<endl;
    Genoma cruza = crossover_BLOQUES(poblacion[0],poblacion[1], 1);
    // cerr<<"----MUTADO----";cerr<<endl;
    cerr<<"----CROSSOVER----";cerr<<endl;
    // cerr<<"----DIFF----";cerr<<endl;
    for (unsigned int i=0;i<genoma_size;i++) {cerr<<cruza[i]<<"  ";} cerr<<endl;
    // auto puntos=fitness_dif_goles(poblacion,10,5, 5);
    return 0;
}
Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        unsigned int proba_mutacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        double fracc_conservar,
                        function<vector<int>(vector<Genoma> &poblacion)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> > (vector<Genoma> &poblacion,
                                                vector<int> &puntajes,
                                                double fracc_poblacion)> seleccion,
                        function<Genoma(Genoma &individuo, unsigned int proba_mutacion)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b, unsigned int proba_mutacion)> crossover ){

    vector<Genoma> generacion = poblacion_inicial(tamanio_poblacion);
    vector<Genoma> generacion_siguiente = generacion;

    for (unsigned int i = 1; i < generaciones; ++i) {
        generacion = generacion_siguiente;

        vector<int> puntajes = fitness(generacion); // me ordena ambas puntajes y generación de mayor a menor puntaje

        pair<vector<Genoma>,vector<Genoma> > divididos = seleccion(generacion, puntajes, fracc_conservar);

        vector<Genoma> cruzados = hacer_crossover(divididos.second, mutacion, proba_mutacion, crossover);

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

    for (unsigned int i = 0; i < tamanio_poblacion; ++i) {
        Genoma actual;
        for (int j = 0; j < genoma_size; ++j) {
            double rand_num = _distribucion(_generador);
            actual.push_back(rand_num);
            cerr<<rand_num<<endl;
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

        }
    }

    // ADEMÁS TENGO QUE ORDENAR LOS PUNTAJES Y GENOMAS PARA QUE ESTÉN DE MAYOR A MENOR FITNESS
    vector<tuple<int, int, Genoma> > todos_juntos (poblacion.size());
    for (unsigned int i = 0; i < poblacion.size(); i++) {
        todos_juntos.push_back(make_tuple(puntos[i],i,poblacion[i]));
    }

    stable_sort (todos_juntos.begin(), todos_juntos.end());

    for (auto e : todos_juntos) {
        int indice = get<1>(e);
        puntos[indice] = get<0>(e);
        poblacion[indice] = get<2>(e);
    }

    return puntos;
}
vector<int> fitness_dif_goles(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total){

// NO CONTEMPLA EMPATES. Si gana le doy un punto más.
    vector<int> dif_goles(poblacion.size(), 0);

    for (unsigned int i = 0; i < poblacion.size(); i++) {
        for (unsigned int j = i + 1 ; j < poblacion.size(); ++j) {
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

    // ADEMÁS TENGO QUE ORDENAR LOS PUNTAJES Y GENOMAS PARA QUE ESTÉN DE MAYOR A MENOR FITNESS
    vector<tuple<int, int, Genoma> > todos_juntos (poblacion.size());
    for (unsigned int i = 0; i < poblacion.size(); i++) {
        todos_juntos.push_back(make_tuple(dif_goles[i],i,poblacion[i]));
    }

    stable_sort (todos_juntos.begin(), todos_juntos.end());

    for (auto e : todos_juntos) {
        int indice = get<1>(e);
        dif_goles[indice] = get<0>(e);
        poblacion[indice] = get<2>(e);
    }
    // for (auto e: dif_goles)
    // {
    // cerr<<e<<"\t";
    // }
    // cerr<<endl;


    return dif_goles;
}

pair<vector<Genoma>,vector<Genoma> > seleccion_por_puntaje(vector<Genoma> &poblacion,
                                                vector<int> &puntajes,
                                                double fracc_poblacion){
    vector<Genoma> intactos;
    vector<Genoma> modificar;

    int cantidad_que_pasa = (int)poblacion.size()*fracc_poblacion;
    int i = 0;
    while( i < cantidad_que_pasa ) {
        intactos.push_back(poblacion[i]);
        i++;
    }
    while (i < (int)poblacion.size()) {
        modificar.push_back(poblacion[i]);
        i++;
    }

    return make_pair(intactos,modificar);
}
pair<vector<Genoma>,vector<Genoma> > seleccion_por_cantidad(vector<Genoma> &poblacion,
                                                vector<int> &puntajes,
                                                double varianza){
    vector<Genoma> intactos;
    vector<Genoma> modificar;

    double puntos_min = puntajes[0] - (puntajes[0]*varianza);

    for (unsigned int i = 0; i < poblacion.size(); i++) {
        if (puntajes[i] < puntos_min ) {
            modificar.push_back(poblacion[i]);
        } else {
            intactos.push_back(poblacion[i]);
        }
    }

    return make_pair(intactos,modificar);
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
                                unsigned int proba_mutacion,
                                function<Genoma (Genoma &a,Genoma &b, unsigned int proba_mutacion)> crossover){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    // std::uniform_real_distribution<double> _dist_continua{0.0,1.0};
    int ultimo_nindice = poblacion.size()-1;
    std::uniform_int_distribution<int> _dist_discreta{0,ultimo_nindice};

    map<int,vector<int> > pares;
    int pob_size = (int)poblacion.size();
    vector<Genoma> nueva_gen;
    for (int i = 0; i < pob_size; i++) {
        nueva_gen.push_back(crossover(poblacion[i], poblacion[(i+1)%pob_size], proba_mutacion));
        nueva_gen.push_back(crossover(poblacion[i], poblacion[(i+4)%pob_size], proba_mutacion));
    }
    return nueva_gen;   // podríamos estar cruzando a los mismos dos veces.
}

Genoma crossover_BLOQUES(Genoma &a,Genoma &b, unsigned int proba_mutacion){ // por bloques semánticos
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_int_distribution<int> _dist_discreta{0,1};

    Genoma cruza(genoma_size);
    auto &primero = (_dist_discreta(_generador))? a : b; // ATAQUE
    auto &segundo = (_dist_discreta(_generador))? a : b; // DEFENSA
    auto &tercero = (_dist_discreta(_generador))? a : b; // PROBABILIDADES DE QUITE

    for (int i = inicio_ataque; i <= fin_ataque; i++) {
        cruza[i] = primero[i];
    }

    for (int i = inicio_defensa; i <= fin_defensa; i++) {
        cruza[i] = segundo[i];
    }
    for (int i = inicio_proba; i <= fin_proba; i++) {
        cruza[i] = tercero[i];
    }
    return cruza;
}
Genoma crossover_RANDOM(Genoma &a,Genoma &b, unsigned int proba_mutacion){ // mezcla random
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_int_distribution<int> _dist_discreta{0,1};

    Genoma cruza(genoma_size);

    for (int i = 0; i < genoma_size; i++) {
        auto &progenitor = (_dist_discreta(_generador))? a : b;
        cruza[i] = progenitor[i];
    }

    return cruza;
}

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