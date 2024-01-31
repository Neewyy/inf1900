/*
Travail                                   : Travail pratique No. 2 sur les machines à états finis logicielles
Section #                                 : 03
Équipe #                                  : 69
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications matérielles (Broches I/O) : D2 est l'entré alors que PA0 et PA1 sont les sorties.
Description du programme                  : 
Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. Si le bouton-poussoir libre pour usage général est pesé, la DEL affiche la couleur AMBER. 
Quand le bouton-poussoir est relâché, la DEL devient verte. Si le bouton est de nouveau pesé, la DEL prend la couleur rouge encore. Quand il est relâché, la DEL s'éteint. 
Si le bouton est de nouveau pesé, la DEL affiche la couleur verte. 
Quand il est relâché, la DEL tourne au rouge ce qui fait que la carte mère est de retour à son état initial et tout peut recommencer.
+--------------+--------+--------------+-------+
| État présent | PIN D2 | État suivant | PORTA |
+--------------+--------+--------------+-------+
| RED_ONE 1    | 0      | RED_ONE 1    | 2     |
+--------------+--------+--------------+-------+
| RED_ONE 1    | 1      | AMBER        | 2     |
+--------------+--------+--------------+-------+
| AMBER        | 1      | AMBER        | X     | Alterne entre la couleur vert et rouge très rapidement
+--------------+--------+--------------+-------+
| AMBER        | 0      | GREEN_ONE 1  | 2     |
+--------------+--------+--------------+-------+
| GREEN_ONE 1  | 1      | RED_ONE 2    | 1     |
+--------------+--------+--------------+-------+
| GREEN_ONE 1  | 0      | GREEN_ONE 1  | 1     |
+--------------+--------+--------------+-------+
| RED_ONE 2    | 1      | RED_ONE 2    | 2     |
+--------------+--------+--------------+-------+
| RED_ONE 2    | 0      | Grey 1       | 2     |
+--------------+--------+--------------+-------+
| Grey 1       | 1      | GREEN_ONE 2  | 0     |
+--------------+--------+--------------+-------+
| Grey 1       | 0      | Grey 1       | 0     |
+--------------+--------+--------------+-------+
| GREEN_ONE 2  | 1      | GREEN_ONE 2  | 1     |
+--------------+--------+--------------+-------+
| GREEN_ONE 2  | 0      | RED_ONE 1    | 1     |
+--------------+--------+--------------+-------+
*/
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
#include <avr/io.h>
const int TRANSITION_DELAY = 10;
const int D2 = 1 << PD2;
const int GREEN_ONE_LED = 1 << PA0;
const int RED_ONE_LED = 1 << PA1;
const int OFF_LED = 1 << PA2;
bool debounce()
{
    if (PIND & D2)
    {
        _delay_ms(TRANSITION_DELAY);
        return true;
    }
    return false;
}
void AMBERColor
()
{
    do
    {
        PORTA = RED_ONE_LED;
        debounce();
        PORTA = GREEN_ONE_LED;
    } while (debounce());
}
enum class State
{
    RED_ONE,
    AMBER,
    GREEN_ONE,
    RED_TWO,
    GREY,
    GREEN_ONE_TWO
};
int main()
{
    DDRA = 0xff; 
    DDRD = 0x00;
    State presentState = State::RED_ONE;
    while (true)
    {
        debounce();
        switch (presentState)
        {
        case State::RED_ONE:
            PORTA = RED_ONE_LED;
            if (debounce())
            {
                presentState = State::AMBER;
            }
            break;
        case State::AMBER:
            AMBERColor
            ();
            presentState = State::GREEN_ONE;
            break;
        case State::GREEN_ONE:
            PORTA = GREEN_ONE_LED;
            if (debounce())
            {
                presentState = State::RED_TWO;
            }
            break;
        case State::RED_TWO:
            PORTA = RED_ONE_LED;
            if !(debounce())
            {

                presentState = State::GREY;
            }
            break;
        case State::GREY:
            PORTA = OFF_LED;
            if (debounce())
            {
                presentState = State ::GREEN_ONE_TWO;
            }
            break;
        case State ::GREEN_ONE_TWO:
            PORTA = GREEN_ONE_LED;
            if !debounce()
            {
                presentState = State::RED_ONE;
            }
            break;
        }
    }
}
