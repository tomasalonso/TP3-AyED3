
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

friend std::ostream& operator<<(std::ostream& out, const Arbitro &a) {
	vector<Jugador> *e1;
	vector<Jugador> *e2;

	if (a._envio) { // TODO: ponerle un nombre lindo
		e1 = &a._t._jugadoresI;
		e2 = &a._t._jugadoresD;
	} else {
		e2 = &a._t._jugadoresI;
		e1 = &a._t._jugadoresD;
	}
	a._envio = !a._envio;

	// Envía el estado
	// Equipo A
	// Envia cada jugador y por cada uno chequea si tiene la pelota
	for (unsigned int i = 0; i < cant_jug; i++) {
		Jugador &j = *e1[i];

		out << i << " " << j.pos().x() << " " << j.pos().y() << " ";
		if (&j == a._t._jugPelota) {
 			out << "CON_PELOTA" << std::endl;
		} else {
			out << "SIN_PELOTA" << std::endl;
		}
	}
	// Equipo B
	// Envia cada jugador y por cada uno chequea si tiene la pelota
	for (unsigned int i = 0; i < cant_jug; i++) {
		Jugador &j = *e2[i];

		out << i << " " << j.pos().x() << " " << j.pos().y() << " ";
		if (&j == a._t._jugPelota) {
 			out << "CON_PELOTA" << std::endl;
		} else {
			out << "SIN_PELOTA" << std::endl;
		}
	}
}

friend std::istream& operator>>(std::istream& in, const Arbitro &a) {
	vector<Jugador> *e1;
	vector<Jugador> *e2;

	if (a._envio) { // TODO: ponerle un nombre lindo
		e1 = &a._t._jugadoresI;
		e2 = &a._t._jugadoresD;
	} else {
		e2 = &a._t._jugadoresI;
		e1 = &a._t._jugadoresD;
	}
	// Recibe movimientos de un equipo
	// Se fija que equipo es
	vector<Movimiento>  movs;

	in >> movs;

	a._t.actualizar(movs, a._envio);
}
