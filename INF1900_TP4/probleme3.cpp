/*
Travail                                   : TP4 - Probleme 3
Section #                                 : 03
Équipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


void ajustementPwm(uint8_t valeur)
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
	// page 130 de la description technique du ATmega324PA)
	OCR1A = valeur; // valeur de comparaison pour la sortie OC1A
	OCR1B = valeur; // valeur de comparaison pour la sortie OC1B

	// division d'horloge par 8 - implique une fréquence de PWM fixe
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << CS11) | (1 << WGM12) | (1 << WGM13);
	TCCR1C = 0;
}

int main()
{
	DDRD = (1 << PD5) | (1 << PD4); //Configurer les broches PD4 et PD5 en sortie pour les signaux PWM
	ajustementPwm(127); //Initialiser le timer1 en mode PWM avec une valeur de comparateur de 127

	wwhile(1) {
		ajustementPwm(0x00); // 0% duty cycle
		_delay_ms(2000);
		ajustementPwm(0x40); // 25% duty cycle
		_delay_ms(2000);
		ajustementPwm(0x80); // 50% duty cycle
		_delay_ms(2000);
		ajustementPwm(0xC0); // 75% duty cycle
		_delay_ms(2000);
		ajustementPwm(0xFF); // 100% duty cycle
		_delay_ms(2000);
		// valeur is always a value between 0 and 255 bc valeur is defined as uint8_t (var is 8-bit so max value is 255)
	}

	return 0;
}