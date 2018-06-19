


class Tablero;

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
	
	void hacerJugada(vector<Movimiento> equipoIzq, vector<Movimiento> equipoDer); //devuelve el string con los estados? le avisa a cada uno directo? es nuestro arbitro asique puede hacer como querrmos, o no? 


private:
	int _tiempo; //sobran?
	int _total;

	Tablero _t; // tiene las prob y los jugadores
}
