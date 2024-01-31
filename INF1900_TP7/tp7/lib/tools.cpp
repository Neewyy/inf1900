/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "tools.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * 
Nom : setDDR
Description : Configure le port en entr�e ou en 
sortie. Mode est soit "input" ou "output".
* * * * * * * * * * * * * * * * * * * * * * * * */
void Tools::setDDR(char ddr, uint8_t mode) {
	switch (ddr) {
	case 'A':
		DDRA = mode;
		break;
	case 'B':
		DDRB = mode;
		break;
	case 'C':
		DDRC = mode;
		break;
	case 'D':
		DDRD = mode;
		break;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
Nom : setPinCombo
Description : Prend une combinaison de pins (ex. 
01, 23, 45, 67) en entr�e. D�finir quels pins 
seront utilis�s (surtout pour la LED).
* * * * * * * * * * * * * * * * * * * * * * * * */
void Tools::setPinCombo(int pinCombo) {
	switch (pinCombo) {
	case 01:
		pin1 = P0;
		pin2 = P1;
		break;
	case 23:
		pin1 = P2;
		pin2 = P3;
		break;
	case 45:
		pin1 = P4;
		pin2 = P5;
		break;
	case 67:
		pin1 = P6;
		pin2 = P7;
		break;
	}
}