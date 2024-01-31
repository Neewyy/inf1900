/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "LED.h"
#include "tools.h"


void LED::greenON(char port, int pinCombo) {
	Tools tool1 = Tools();
	switch (port) {
	case 'A':
		PORTA = 1 << tool1.pin1;
		break;
	case 'B':
		PORTB = 1 << tool1.pin1;
		break;
	case 'C':
		PORTC = 1 << tool1.pin1;
		break;
	case 'D':
		PORTD = 1 << tool1.pin1;
		break;
	}
}

void LED::redON(char port, int pinCombo) {
	Tools tool2 = Tools();
	switch (port) {
	case 'A':
		PORTA = 1 << tool2.pin2;
		break;
	case 'B':
		PORTB = 1 << tool2.pin2;
		break;
	case 'C':
		PORTC = 1 << tool2.pin2;
		break;
	case 'D':
		PORTD = 1 << tool2.pin2;
		break;
	}
}

void LED::amberON(char port, int pinCombo) {
	switch (port) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
		greenON(port, pinCombo);
		_delay_ms(10);
		redON(port, pinCombo);
		_delay_ms(10);
		break;
	}
}

void LED::OFF(char port, int pinCombo) {
	switch (port) {
	case 'A':
		PORTA = LED_OFF_;
		break;
	case 'B':
		PORTB = LED_OFF_;
		break;
	case 'C':
		PORTC = LED_OFF_;
		break;
	case 'D':
		PORTD = LED_OFF_;
		break;
	}
}