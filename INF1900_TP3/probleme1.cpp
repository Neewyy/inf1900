/*
Travail                                   : TP3 - Probleme 2
Section #                                 : 03
Équipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : Ce programme permet d'alterner entre rouge et vert, en baissant la luminosite petit-a-petit
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


void pwm(int colour) {
	int isWhite = 0x00;

	for (int i = 3000; i > 0; i--) {
		double ON = i / 30; // first iteration: ON = 3000/30 = 100, ON 100%
		double OFF = 100 - ON;

		PORTA = colour;
		for (int j = 0; j < ON; j++) {
			_delay_ms(0.01); // when ON is at 100%: for loops 100 times, 100*0.01 = 1ms
		}
		PORTA = isWhite;
		for (int j = 0; j < OFF; j++) {
			_delay_ms(0.01);
		}
	}
}

int main()
{
	DDRA = 0xff;
	int isGreen = 0x01;
	int isRed = 0x02;

	while(true) {
		pwm(isRed);
		pwm(isGreen);
	}
	return 0;
}
