/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef BUTTON_PRESSED_H
#define BUTTON_PRESSED_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class Button {
public:
	Button() : buttonStatus_(false), pressed_(1 << PD2) {}
	bool isPressed();
	void initalizeButtonINT();
private:
	bool buttonStatus_;
	int pressed_;
};

#endif
