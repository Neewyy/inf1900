/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <avr/io.h>


enum PIN_VALUE {
	P0 = 0,
	P1 = 1,
	P2 = 2,
	P3 = 3,
	P4 = 4,
	P5 = 5,
	P6 = 6,
	P7 = 7
};

class Tools {
public:
	Tools() = default;
	void setDDR(char ddr, uint8_t mode);
	void setPinCombo(int pinCombo);
	int pin1, pin2;
	const uint8_t output = 0xFF;
	const uint8_t input = 0x00;
};

#endif