#include "funGenetico.hpp"



int main()
{

    // string fit,sel,mut,cross;

    // cin>>fit>>sel>>mut>>cross;

    vector<
        function<vector<int>(vector<Genoma> &poblacion, unsigned int n, unsigned int m, unsigned int total)>
                > fitness = {fitness_puntos, fitness_dif_goles};

    vector<
        function<pair<vector<Genoma>,vector<Genoma> > (vector<Genoma> &poblacion, vector<int> &puntajes, double fracc_poblacion)>
                > seleccion = {seleccion_por_puntaje, seleccion_por_cantidad};

    vector<
        function<void(Genoma &individuo, double proba_mutacion)>
                > mutacion = {mutacion_A, mutacion_B};

    vector<
        function<Genoma(Genoma &a, Genoma &b)>
                > crossover = {crossover_BLOQUES, crossover_RANDOM};

    vector<string> f_names = {"fitness_puntos", "fitness_dif_goles"};
    vector<string> s_names = {"seleccion_por_puntaje", "seleccion_por_cantidad"};
    vector<string> m_names = {"mutacion_A", "mutacion_B"};
    vector<string> c_names = {"crossover_BLOQUES", "crossover_RANDOM"};

    vector<int> enes = { 10 };
    vector<int> emes = { 5 };
    vector<int> tiempos = { 70 };
    vector<int> generaciones = { 30 };
    vector<int> poblaciones = { 20 , 30 };

    vector<double> fracciones = { 0.2 , 0.4 };
    vector<double> probas = { 0.3 , 0.6 , 0.9 };


    for (unsigned int i = 0; i < fitness.size(); i++) {
        for (unsigned int j = 0; j < seleccion.size(); j++) {
            for (unsigned int k = 0; k < mutacion.size(); k++) {
                for (unsigned int l = 0; l < crossover.size(); l++) {
                    for (int N : enes) {
                    for (int M : emes) {
                    for (int Tiempo : tiempos) {
                    for (double Fraccion : fracciones) {
                    for (double Proba : probas) {
                    for (double pob : poblaciones) {

                        cerr<<"Parametros:\n "<<"N\tM\tTiempo\tFitness\t\tSeleccion\t\tMutacion\tCrossover\t\tFraccion\tProba mutacion\n";
                        cerr<<N<<"\t"<<M<<"\t"<<Tiempo<<"\t"<<f_names[i]<<"\t"<<s_names[j]<<"\t"<<m_names[k]<<"\t"<<c_names[l]<<"\t"<<Fraccion<<"\t\t"<<Proba<<"\n\n\n";

                        Genoma la_posta = hacer_genetico(generaciones[0],
                                                         pob,
                                                         Proba,
                                                         N,
                                                         M,
                                                         Tiempo,
                                                         Fraccion,
                                                         fitness[i],
                                                         seleccion[j],
                                                         mutacion[k],
                                                         crossover[l]               );

                        cerr<<"---------------------------------------------  "<<endl<<endl;
                        cerr<<"{ ";
                        for (auto e: la_posta) {cerr<<e<<"  ";}
                        cerr<<" }\n ------------- FIN EJECUCIÓN -------------  "<<endl<<endl<<endl;

                    }}}}}}
                }
            }
        }
    }

    // Genoma la_posta = hacer_genetico(5, 40, 0.7, 10, 5, 30, 0.3,
    //                                  fitness_dif_goles, seleccion_por_puntaje,
    //                                  mutacion_A, crossover_BLOQUES);

    // auto poblacion = poblacion_inicial(5);
        // for (unsigned int i=0;i<poblacion.size();i++) {for(auto e : (poblacion)[i] ){cerr<<e<<"  ";} cerr<<endl;}
    // Genoma copia = poblacion[0];
    // for (auto e: poblacion[1]) {cerr<<e<<"  ";} cerr<<endl;
    // Genoma cruza = crossover_BLOQUES(poblacion[0],poblacion[1], 1);
    // vector<int> puntos={202,200,198,140,120};
    // auto seleccion = seleccion_por_puntaje(poblacion,puntos,0.4);
    // cerr<<"----MUTADO----";cerr<<endl;
    // cerr<<"----CROSSOVER----";cerr<<endl;
    // cerr<<"----DIFF----";cerr<<endl;
    // for (unsigned int i=0;i<seleccion.first.size();i++) {for(auto e : (seleccion.first)[i] ){cerr<<e<<"  ";} cerr<<endl;}
    // auto puntos=fitness_dif_goles(poblacion,10,5, 5);
    return 0;
}
Genoma hacer_genetico(  unsigned int generaciones,
                        unsigned int tamanio_poblacion,
                        double proba_mutacion,
                        unsigned int n,
                        unsigned int m,
                        unsigned int total,
                        double fracc_conservar,
                        function<vector<int>(vector<Genoma> &poblacion, unsigned int n,
                                unsigned int m, unsigned int total)> fitness,
                        function<pair<vector<Genoma>,vector<Genoma> > (vector<Genoma> &poblacion,
                                                vector<int> &puntajes,
                                                double fracc_poblacion)> seleccion,
                        function<void(Genoma &individuo, double proba_mutacion)> mutacion,
                        function<Genoma(Genoma &a, Genoma &b)> crossover ){

    auto inicio = high_resolution_clock::now();

    vector<Genoma> generacion = poblacion_inicial(tamanio_poblacion);
    vector<int> puntajes;
    vector<Genoma> generacion_siguiente = generacion;

    for (unsigned int i = 0; i < generaciones; ++i) {
        // for (unsigned int i=0;i<generacion.size();i++) {for(auto e : (generacion)[i] ){cerr<<e<<"  ";} cerr<<endl;}
        generacion = generacion_siguiente;

        puntajes = fitness(generacion, n, m, total); // me ordena ambas puntajes y generación de mayor a menor puntaje

        int puntaje_max = 0;
        int puntaje_max_ind = 0;
        int puntaje_min = 99999999;
        // int puntaje_min_ind = 0;

        cerr<<"Puntajes:\n";
        for (unsigned int k = 0; k < puntajes.size(); k++) {
            cerr<<puntajes[k]<<" ";
            if (puntajes[k] > puntaje_max) {
                puntaje_max = puntajes[k];
                // puntaje_max_ind = k;
            }
            if (puntajes[k] < puntaje_min) {
                puntaje_min = puntajes[k];
                // puntaje_min_ind = k;
            }
        }
        cerr<<endl<<endl;

        cerr<<"Generación: "<<i<<"\tTamaño: "<<generacion.size()<<"\tPuntaje máximo: "<<puntaje_max<<"\tPuntaje mínimo: "<<puntaje_min<<endl;
        // for (unsigned int i=0;i<generacion.size();i++) {cerr<<"P: "<<puntajes[i]<<" ";for(unsigned int j=0;j<(generacion)[i].size();j++ ){
            // if(j == 13){cerr<<endl<<"      ";}cerr<<generacion[i][j]<<"  ";} cerr<<endl;}
        for(auto e : generacion[puntaje_max_ind] ){cerr<<e<<"  ";} cerr<<endl<<endl;


        pair<vector<Genoma>,vector<Genoma> > divididos = seleccion(generacion, puntajes, fracc_conservar);

        vector<Genoma> cruzados = hacer_crossover(generacion, mutacion, proba_mutacion, crossover, (divididos.first).size());

        generacion_siguiente = divididos.first;

        generacion_siguiente.insert(generacion_siguiente.end(), cruzados.begin(), cruzados.end());
    }

    auto fin = high_resolution_clock::now();
    auto runtime = duration_cast<minutes>(fin - inicio).count();
    cerr<<"Tiempo: "<<runtime<<" min"<<endl;
    cerr<<"Mejor puntaje: "<<puntajes[0]<<endl;
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
            // cerr<<rand_num<<endl;
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
            // cerr<<"Juegan i: "<<i<<" vs. j: "<<j<<endl;
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
    vector<tuple<int, Genoma> > todos_juntos;
    for (unsigned int i = 0; i < poblacion.size(); i++) {
        todos_juntos.push_back(make_tuple(puntos[i],poblacion[i]));
    }

    stable_sort (todos_juntos.rbegin(), todos_juntos.rend());

    int k = 0;

    for (auto e : todos_juntos) {
        puntos[k] = get<0>(e);
        poblacion[k] = get<1>(e);

        k++;
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
    vector<tuple<int, Genoma> > todos_juntos;
    for (unsigned int i = 0; i < poblacion.size(); i++) {
        todos_juntos.push_back(make_tuple(dif_goles[i],poblacion[i]));
    }

    stable_sort (todos_juntos.rbegin(), todos_juntos.rend());

    int k = 0;

    for (auto e : todos_juntos) {
        dif_goles[k] = get<0>(e);
        poblacion[k] = get<1>(e);

        k++;
    }
    return dif_goles;
}

pair<vector<Genoma>,vector<Genoma> > seleccion_por_puntaje(vector<Genoma> &poblacion,
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
pair<vector<Genoma>,vector<Genoma> > seleccion_por_cantidad(vector<Genoma> &poblacion,
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

void mutacion_A(Genoma &individuo, double proba_mutacion){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_real_distribution<double> _dist_continua{0.0,1.0};
    std::uniform_int_distribution<int> _dist_discreta{0,genoma_size-1};

    for (int i = 0; i < genoma_size; i++) {

        double muto = _dist_continua(_generador);
        if (muto <= proba_mutacion) {
            individuo[i] = _dist_continua(_generador);
        }
    }
}

void mutacion_B(Genoma &individuo, double proba_mutacion){
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
                                function<void(Genoma &individuo,
                                                double proba_mutacion)> mutacion,
                                double proba_mutacion,
                                function<Genoma (Genoma &a,Genoma &b)> crossover,
                                unsigned int best){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    // std::uniform_real_distribution<double> _dist_continua{0.0,1.0};
    int ultimo_nindice = poblacion.size()-1;
    std::uniform_int_distribution<int> _dist_discreta{0,ultimo_nindice};

    // map<int,vector<int> > pares;
    int pob_size = (int)poblacion.size()- best;
    vector<Genoma> nueva_gen;
    for (int i = 0; i < pob_size; i++) {
        nueva_gen.push_back(crossover(poblacion[i], poblacion[(i+1)%pob_size]));
    }

    for (auto e: nueva_gen) {

        // for (auto j: e) {cerr<<j<<"  ";} cerr<<endl;
        mutacion(e, proba_mutacion);
    // cerr<<"----MUTADO----";cerr<<endl;
        // for (auto j: e) {cerr<<j<<"  ";} cerr<<endl;
    }
    return nueva_gen;   // podríamos estar cruzando a los mismos dos veces.
}

Genoma crossover_BLOQUES(Genoma &a,Genoma &b){ // por bloques semánticos
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine _generador (seed);
    std::uniform_int_distribution<int> _dist_discreta{0,1};

    Genoma cruza(genoma_size);

    // DISTANCIA JUGADOR ARCO
    auto &d_j_a = (_dist_discreta(_generador))? a : b;
    // DISTANCIA PELOTA ARCO
    auto &d_p_a = (_dist_discreta(_generador))? a : b;
    // DISTANCIA RIVAL
    auto &d_r = (_dist_discreta(_generador))? a : b;
    // DISTANCIA JUGADOR PELOTA
    auto &d_j_p = (_dist_discreta(_generador))? a : b;
    // DISTANCIA JUGADOR LATERAL
    auto &d_j_lat = (_dist_discreta(_generador))? a : b;
    // AREA
    auto &area_ocupada = (_dist_discreta(_generador))? a : b;
    // PROBABILIDADES DE QUITE
    auto &quite = (_dist_discreta(_generador))? a : b;

    for (int i = inicio_dist_j_a; i <= fin_dist_j_a; i++) {
        cruza[i] = d_j_a[i];
    }

    for (int i = inicio_dist_p_a; i <= fin_dist_p_a; i++) {
        cruza[i] = d_p_a[i];
    }

    for (int i = inicio_dist_rival; i <= fin_dist_rival; i++) {
        cruza[i] = d_r[i];
    }

    for (int i = inicio_dist_j_p; i <= fin_dist_j_p; i++) {
        cruza[i] = d_j_p[i];
    }

    for (int i = inicio_dist_j_lateral; i <= fin_dist_j_lateral; i++) {
        cruza[i] = d_j_lat[i];
    }

    cruza[area] = area_ocupada[area];

    for (int i = inicio_probas; i <= fin_probas; i++) {
        cruza[i] = quite[i];
    }

    return cruza;
}
Genoma crossover_RANDOM(Genoma &a,Genoma &b){ // mezcla random
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
                          Jugador(1, Posicion(1,4), jugA[prob1]),
                          Jugador(2, Posicion(4,3), jugA[prob2])
    });
    const vector<Jugador> jD({
                          Jugador(0, Posicion(6,3), jugB[prob0]),
                          Jugador(1, Posicion(9,1), jugB[prob1]),
                          Jugador(2, Posicion(9,4), jugB[prob2])
    });


    Equipo equipoI(jugA, false);
    Equipo equipoD(jugB, true);

    Tablero tablero(m, n, total, jI, jD);

    while (!tablero.terminado()) {
        tablero.actualizar(
                           equipoI.turno(tablero),
                           equipoD.turno(tablero)
                           );
    }

    return tablero.goles();
}