TO-DO
------

* En Equipo::genJugadas2 revisar que la dirección de patear pelota está relacionada a la dirección k. Esto hace que si el tercer jugador no tiene la pelota haya dos jugadores que tiren/se muevan en la misma dirección. ¿Está bien esto?

* Funciones a hacer:
    + vector<int> Tablero::distJugadorAlArco(bool enDerecha)
    + int Tablero::distPelotaArco(bool enDerecha)
    + int Tablero::cercaniaARival(Jugador&)
    + int Tablero::areaCubierta(bool enDerecha)
    + bool Tablero::pelotaEnPosesion() const
    + int Tablero::puntaje(bool enDerecha) const
    + const Jugador& Tablero::jugadorPelota() const
    + int Tablero::N()
    + int Tablero::M()