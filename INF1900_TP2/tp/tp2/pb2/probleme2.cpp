/*
Travail                                   : TP2 - Probleme 2
Section #                                 : 03
Équipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : Initialement, affiche la couleur rouge. Apres un appui la DEL devient ambre et apres un relachement, 
                                            elle devient verte. Apres un deuxieme appui, elle devient rouge et en apres avoir relacher elle s'eteint. 
                                            Enfin, elle s'allume en vert apres le troisieme appui et revient a l'etat initial rouge en relachant.
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


enum class State { RED1, AMBER, GREEN1, RED2, OFF, GREEN2 };

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

void isAmber()
{
    int isGreen = 0x01;
    int isRed = 0x02;

    do {
        PORTA = isGreen;
        isPressed();
        PORTA = isRed;
    }
    while (isPressed());
}

int main()
{
    State state = State::RED1;
    DDRA = 0xff;
    DDRD = 0x00;
    int isGreen = 0x01;
    int isRed = 0x02;
    int isWhite = 0x00;

    while(true) {
        switch(state) {
            case State::RED1:
                PORTA = isRed;
                if (isPressed()) {
                    state = State::AMBER;
                }
                break;
            case State::AMBER:
                isAmber();
                if (!(isPressed())) {
                    state = State::GREEN1;
                }
                break;
            case State::GREEN1:
                PORTA = isGreen;
                if (isPressed()) {
                    state = State::RED2;
                }
                break;
            case State::RED2:
                PORTA = isRed;
                if (!(isPressed())) {
                    state = State::OFF;
                }
                break;
            case State::OFF:
                PORTA = isWhite;
                if (isPressed()) {
                    state = State::GREEN2;
                }
                break;
            case State::GREEN2:
                PORTA = isGreen;
                if (!(isPressed())) {
                    state = State::RED1;
                }
                break;
        }
    }
    return 0;
}