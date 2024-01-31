/*
Travail                                   : TP6 - Probleme 2
Section #                                 : 03
�quipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/

// Si la lumière est basse (en cachant la photorésistance), la DEL prendra la couleur verte.
// Si la lumière est à un bon niveau(lumière ambiante), la DEL tournera à l'ambré.
// Si la lumière est trop forte(photorésistance sous une lampe de poche), la DEL devient rouge.

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

const int LED_OFF = 0;
const int LED_GREEN = (1 << PB0);
const int LED_RED = (1 << PB1);
const uint16_t AMBIANT_THRESHOLD = 10; // difference between LOW, AMBIENT AND HIGH light

void LED_AMBER() {
    PORTB = LED_GREEN;
    _delay_ms(10);
    PORTB = LED_RED;
    _delay_ms(10);
}

enum class LedState { OFF, GREEN, AMBER, RED };


int main() {
    DDRA = 0x00;
    DDRB = 0xff;

    can adc;

    LedState ledState = OFF;
    bool ambreFlag = false;

    while (true) {
		uint16_t light = adc.lecture(0) >> 2;

        if (light > AMBIANT_THRESHOLD)
            ledState = RED;
        else if (light < AMBIANT_THRESHOLD)
            ledState = GREEN;
        else {
            if (ambreFlag)
                ledState = GREEN;
            else
                ledState = RED;
            ambreFlag = !ambreFlag;
        }

        switch (ledState) {
        case OFF:
			PORTB = LED_OFF;
            break;
        case GREEN:
			PORTB = LED_GREEN;
            break;
        case RED:
			PORTB = LED_RED;
            break;
        case AMBER:
			LED_AMBER();
            break;
        }

        _delay_ms(10);
    }

    return 0;
}
