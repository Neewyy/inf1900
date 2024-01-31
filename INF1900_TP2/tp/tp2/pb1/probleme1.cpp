/*
Travail                                   : TP2 - Probleme 1
Section #                                 : 03
Équipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : Ce programme permet de faire allumer une DEL en vert apres le trois appuis-relachement
											sur un bouton poussoir.
+--------------+-------------+---------------+--------+--------+
| Etat present | PIND2       | Etat prochain | PORTA1 | PORTA0 |
+--------------+-------------+---------------+--------+--------+
| OFF          | 0 (relache) | OFF           | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| OFF          | 1 (appuye)  | PRESS1        | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| PRESS1       | 0           | RELEASE1      | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| PRESS1       | 1           | PRESS1        | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| RELEASE1     | 0           | RELEASE1      | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| RELEASE1     | 1           | PRESS2        | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| PRESS2       | 0           | RELEASE2      | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| PRESS2       | 1           | PRESS2        | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| RELEASE2     | 0           | RELEASE2      | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| RELEASE2     | 1           | ON            | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| ON           | 0           | OFF           | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| ON           | 1           | ON            | 1      | 0      |
+--------------+-------------+---------------+--------+--------+
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


enum class State { OFF, PRESS1, RELEASE1, PRESS2, RELEASE2, ON };

bool isPressed()
{
	const uint8_t DELAY_DEBOUNCE = 10;

	if (PIND & 0x04) {
		_delay_ms(DELAY_DEBOUNCE);
		if (PIND & 0x04) {
			return true;
		}
	}
	return false;
}

int main()
{
	State state = State::OFF;
	DDRA = 0xff;
	DDRD = 0x00;
	int isGreen = 0x01;
	int isWhite = 0x00;
	const uint16_t DELAY_GREEN = 2000;

	while(true) {
		switch(state) {
			case State::OFF:
				PORTA = isWhite;
				if (isPressed()) {
					state = State::PRESS1;
				}
				break;
			case State::PRESS1:
				if (!isPressed()) {
					state = State::RELEASE1;
				}
				break;
			case State::RELEASE1:
				if (isPressed()) {
					state = State::PRESS2;
				}
				break;
			case State::PRESS2:
				if (!isPressed()) {
					state = State::RELEASE2;
				}
				break;
			case State::RELEASE2:
				if (isPressed()) {
					state = State::ON;
				}
				break;
			case State::ON:
				if (!isPressed()) {
					PORTA = isGreen;
					_delay_ms(DELAY_GREEN);
					state = State::OFF;
				}
				break;
		}
	}
	return 0;
}