/*
Travail                                   : TP4 - Probleme 2
Section #                                 : 03
�quipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>


volatile uint8_t gMinuterieExpiree = 0; // selon le nom de votre variable
volatile uint8_t gBoutonPoussoir = 0; // selon le nom de votre variable

ISR(TIMER0_OVF_vect) {
	gMinuterieExpiree = 1;
}

ISR(INT0_vect) {
	gBoutonPoussoir = 1;

	// debounce
	_delay_ms(30);
}

void initialisation(void) {
	cli();

	DDRA = 0xff;
	DDRD = 0x00;

	EIMSK |= (1 << INT0);

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA
	EICRA |= (1 << ISC00); // for rising edge
	// |= (1 << ISC00) | (1 << ISC01); for falling edge

	sei();
}

void partirMinuterie(uint16_t duree) {
	gMinuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divis�e par 1024
	// interruption apr�s la dur�e sp�cifi�e
	TCNT1 = 0;
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 = (1 << OCIE1A);

	// The values assigned to TCCR1A, TCCR1B, and TIMSK1 in the code are chosen to configure the 
	// Timer/Counter1 of the microcontroller in Clear Timer on Compare Match (CTC) mode with 
	// a clock prescaler of 1024.

	// TCCR1A = 0; sets the compare output mode to normal port operation and clears any waveform 
	// generation settings.

	// TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); sets the timer in CTC mode by setting the 
	// WGM12 bitand sets the clock prescaler to 1024 by setting the CS12 and CS10 bits.

	// TIMSK1 = (1 << OCIE1A); sets the Output Compare A Match Interrupt Enable(OCIE1A) bit to 1, 
	// which enables the Output Compare A match interrupt.

	// The value of TCNT1 is set to 0 to initialize the timer's count to zero. This is done to ensure 
	// that the timer starts counting from 0 and counts up to the desired value stored in OCR1A. 
	// By setting TCNT1 to 0, the timer will reach the value of OCR1A after the specified duration 
	// and trigger an interrupt, indicating that the timer has expired.
}

int main()
{
	int isGreen = 0x01;
	int isRed = 0x02;
	int isWhite = 0x00;

	// wait 10s
	_delay_ms(10000);

	// flash red for 1/10s
	PORTA = isRed;
	_delay_ms(100);
	PORTA = isWhite;

	// wait for user input or timer elapse
	do {
		// attendre qu'une des deux variables soit modifi�e
		// par une ou l'autre des interruptions.
	} while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);

	// Une interruption s'est produite. Arr�ter toute
	// forme d'interruption. Une seule r�ponse suffit.
	cli();

	// Verifier la r�ponse
	if (gMinuterieExpiree == 1) {
		PORTA = isRed;
	}
	else if (gBoutonPoussoir == 1) {
		PORTA = isGreen;
	}

	return 0;
}