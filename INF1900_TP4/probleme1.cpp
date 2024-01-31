/*
Travail                                   : TP4 - Probleme 1
Section #                                 : 03
�quipe #                                  : 
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
+--------------+-------------+---------------+--------+--------+
| Etat present | PIND2       | Etat prochain | PORTA1 | PORTA0 |
+--------------+-------------+---------------+--------+--------+
| RED1         | 0 (relache) | RED1          | 1      | 0      |
+--------------+-------------+---------------+--------+--------+
| RED1         | 1 (appuye)  | AMBER         | X      | X      | (alterne entre vert et rouge tres rapidement)
+--------------+-------------+---------------+--------+--------+
| AMBER        | 0           | GREEN1        | 0      | 1      |
+--------------+-------------+---------------+--------+--------+
| AMBER        | 1           | AMBER         | X      | X      |
+--------------+-------------+---------------+--------+--------+
| GREEN1       | 0           | GREEN1        | 0      | 1      |
+--------------+-------------+---------------+--------+--------+
| GREEN1       | 1           | RED2          | 1      | 0      |
+--------------+-------------+---------------+--------+--------+
| RED2         | 0           | OFF           | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| RED2         | 1           | RED2          | 1      | 0      |
+--------------+-------------+---------------+--------+--------+
| OFF          | 0           | OFF           | 0      | 0      |
+--------------+-------------+---------------+--------+--------+
| OFF          | 1           | GREEN2        | 0      | 1      |
+--------------+-------------+---------------+--------+--------+
| GREEN2       | 0           | RED1          | 1      | 0      |
+--------------+-------------+---------------+--------+--------+
| GREEN2       | 1           | ON            | 0      | 1      |
+--------------+-------------+---------------+--------+--------+
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>


volatile uint8_t gCurrentState = 0; // selon le nom de votre variable


ISR(INT0_vect) {
    // Delay to debounce the button
    _delay_ms(30);

    // Read the current button state
    gCurrentState = (PIND & (1 << PD2)); // or write:m = (PIND & (1 << 2)) >> 2;

    EIFR |= (1 << INTF0);

    // essayer de mettre des operations ternaires dans le ISR a laplace des les mettre en if dans le switch case
    // var = conf? res_vrai:res_faux;
}

void initialisation(void) {
    cli();

    DDRA = 0xff;
    DDRD = 0x00;

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);


    sei();
}

enum class State { RED1, AMBER, GREEN1, RED2, OFF, GREEN2 };

void isAmber()
{
    int isGreen = 0x01;
    int isRed = 0x02;

    PORTA = isGreen;
    _delay_ms(10);
    PORTA = isRed;
    _delay_ms(10);
}

int main()
{
    initialisation();

    State state = State::RED1;
    int isGreen = 0x01;
    int isRed = 0x02;
    int isWhite = 0x00;

    while (true) {
        switch (state) {
        case State::RED1:
            PORTA = isRed;
            if (gCurrentState) {
                state = State::AMBER;
            }
            break;
        case State::AMBER:
            isAmber();
            if (!(gCurrentState)) {
                state = State::GREEN1;
            }
            break;
        case State::GREEN1:
            PORTA = isGreen;
            if (gCurrentState) {
                state = State::RED2;
            }
            break;
        case State::RED2:
            PORTA = isRed;
            if (!(gCurrentState)) {
                state = State::OFF;
            }
            break;
        case State::OFF:
            PORTA = isWhite;
            if (gCurrentState) {
                state = State::GREEN2;
            }
            break;
        case State::GREEN2:
            PORTA = isGreen;
            if (!(gCurrentState)) {
                state = State::RED1;
            }
            break;
        }
    }

    return 0;
}