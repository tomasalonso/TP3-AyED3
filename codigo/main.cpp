#include <ostream>
#include <istream>
#include <iostream>

#include <sstream> 
#include <string>

#include <unistd.h>

#include "Arbitro.hpp"
#include "Equipo.hpp"

int main() {
	std::stringbuf buffer;
	std::iostream ios(&buffer);

	Arbitro elizondo;
	Equipo equipo1;
	Equipo equipo2;

	for (unsigned int i = 0; i < 10; i++) {
		// Mando jugada
		ios << elizondo;
		ios >> equipo1;
		ios << elizondo;
		ios >> equipo2;

		// Envia jugada
		ios << equipo1;
		ios >> elizondo;
		ios << equipo2;
		ios >> elizondo;
		usleep(1000000);
	}

	return 0;
}