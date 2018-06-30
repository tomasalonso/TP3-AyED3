#include <random>
#include "Tablero.hpp"

using namespace std;

class Arbitro {
  //  Arbitro(parametros iniciales, n m tiempo pos iniciales

  // disputar la pelota

  // ENTRADA / SALIDA
  // << recibir movimiento de un equipo
  // >> enviar estado del tablero al equipo
  //     chequea si termino el partido
public:
	Arbitro(const unsigned int &M, const unsigned int &N,
            const unsigned int &total, const vector<Jugador> eqI, const vector<Jugador> eqD);

	void hacerJugada(vector<Movimiento> equipoIzq, vector<Movimiento> equipoDer);
  //devuelve el string con los estados? le avisa a cada uno directo?
  //es nuestro arbitro asique puede hacer como querramos, o no?

  bool quiteSuelta(Jugador izq, Jugador der);
  bool quitePoseida(Jugador sacador, Jugador posesor);

  friend std::ostream& operator<<(std::ostream& out, const Arbitro &a);
  friend std::istream& operator>>(std::istream& in, const Arbitro &a);


private:
	int _tiempo; //sobran?
	int _total;

  std::default_random_engine _generador;
  std::uniform_real_distribution<double> _distribucion{0.0,1.0};
	Tablero _t; // tiene las prob y los jugadores
};
