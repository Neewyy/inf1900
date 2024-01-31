/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "buttonPressed.h"


bool Button::isPressed() {
	if (PIND & pressed_) {
		_delay_ms(10);
		if (PIND & pressed_)
			return true;
	}
	return false;
}

void Button::initalizeButtonINT() {
	cli();
	
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01) | (1 << ISC00);
	
	sei();
}