
#include "Arbitro.hpp"
#define eqIZQ false
#define eqDER true

using namespace std;

Arbitro::Arbitro(const unsigned int &M, const unsigned int &N,
                 const unsigned int &total,
                 const vector<Jugador> eqI, const vector<Jugador> eqD):
                 _total(total), _t(M, N, total, eqI, eqD) {
                 }


bool Arbitro::quiteSuelta(Jugador izq, Jugador der) {

	double probaIzq = double(izq.probabilidad());
	double probaDer = double(der.probabilidad());

  double numero = _distribucion(_generador);

	bool gana = (numero <= probaIzq/(probaIzq + probaDer));

  return gana;

}

bool Arbitro::quitePoseida(Jugador sacador, Jugador posesor) {

	double probaPosedor = double(posesor.probabilidad());
	double probaSacador = double(sacador.probabilidad());

  double numero = _distribucion(_generador);

  bool quita = (numero <= probaSacador/(probaSacador + (1-probaPosedor)));

  return quita;

}
