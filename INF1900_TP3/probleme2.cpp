/*
Travail                                   : TP3 - Probleme 1
Section #                                 : 03
Équipe #                                  : 
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : Ce programme permet d'alterner entre rouge et vert, en baissant la luminosite petit-a-petit
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 



void motor(int freq, int dutyCycle) {
	int forTwoSec = freq * 2; // 60hz * 2s = 120 loops
	int ON = dutyCycle;
	int OFF = 100 - ON;
	double time = 10 / freq;

	for (int i = 0; i < forTwoSec; i++) {
		PORTA = 0x01;
		for (int j = 0; j < ON; j++) {
			_delay_ms(time);
		}
		PORTA = 0x00;
		for (int j = 0; j < OFF; j++) {
			_delay_ms(time);
		}
	}
	
	// if dutyCycle = 0, then for OFF will iterate 25 times and ON loop will iterate 0 times
	// if freq = 60hz then OFF will do 100 * 0.166666ms = 16.6666ms; 16.6666ms * 120 loops = 2000ms = 2s
}

int main()
{
	DDRB = 0xff;
	DDRD = 0x00;
	
	while (true) {
		motor(60, 0);
		motor(60, 25);
		motor(60, 50);
		motor(60, 75);
		motor(60, 100);

		motor(400, 0);
		motor(400, 25);
		motor(400, 50);
		motor(400, 75);
		motor(400, 100);
	}
  
    return 0; 
}