/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>


class LED {
public:
	LED() = default;
	void greenON(char port, int pinCombo);
	void redON(char port, int pinCombo);
	void amberON(char port, int pinCombo);
	void OFF(char port, int pinCombo);
private:
	const int LED_OFF_ = 0;
};

#endif