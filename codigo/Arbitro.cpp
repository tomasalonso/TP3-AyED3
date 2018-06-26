
#include "Arbitro.hpp"
#define eqIZQ false
#define eqDER true

using namespace std;

Arbitro::Arbitro(const unsigned int &M, const unsigned int &N,
            const unsigned int &total, const vector<Jugador> eqI, 
            const vector<Jugador> eqD) {

	_t = Tablero(&M, &N, &total, eqI, eqD);
}


bool Arbitro::quiteSuelta(Jugador izq, Jugador der) {
	
	double pobraIzq = double(izq.probabilidad());
	double pobraDer = double(der.probabilidad());

  	double numero = _distribucion(_generador);

  	bool gana = (numero <= probaIzq/(probaIzq + probaDer));
  
  	return gana;

}

bool Arbitro::quitePoseida(Jugador sacador, Jugador posesor) {

	double pobraPosedor = double(posedor.probabilidad());
	double pobraSacador = double(sacador.probabilidad());

  	double numero = _distribucion(_generador);

  	bool quita = (numero <= pobraSacador/(pobraSacador + (1-probaPosedor)));

  	return quita;	

}