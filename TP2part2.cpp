/*
Travail                                   : Travail pratique No. 2 sur les machines à états finis logicielles
Section #                                 : 03
Équipe #                                  : 69
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Trinh Huynh Minh Tam Kevin et Charbonneau Étienne
Identifications matérielles (Broches I/O) : D2 est l'entré alors que PA0 et PA1 sont les sorties.
Description du programme                  : 
Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. Si le bouton-poussoir libre pour usage général est pesé, la DEL affiche la couleur AMBER. 
Quand le bouton-poussoir est relâché, la DEL devient verte. Si le bouton est de nouveau pesé, la DEL prend la couleur rouge encore. Quand il est relâché, la DEL s'éteint. 
Si le bouton est de nouveau pesé, la DEL affiche la couleur verte. 
Quand il est relâché, la DEL tourne au rouge ce qui fait que la carte mère est de retour à son état initial et tout peut recommencer.
+--------------+--------+--------------+-------+
| État présent | PIN D2 | État suivant | PORTA |
+--------------+--------+--------------+-------+
| Red 1        | 0      | Red 1        | 2     |
+--------------+--------+--------------+-------+
| Red 1        | 1      | Amber        | 2     |
+--------------+--------+--------------+-------+
| Amber        | 1      | Amber        | X     | Alterne entre la couleur vert et rouge très rapidement
+--------------+--------+--------------+-------+
| Amber        | 0      | Green 1      | 2     |
+--------------+--------+--------------+-------+
| Green 1      | 1      | Red 2        | 1     |
+--------------+--------+--------------+-------+
| Green 1      | 0      | Green 1      | 1     |
+--------------+--------+--------------+-------+
| Red 2        | 1      | Red 2        | 2     |
+--------------+--------+--------------+-------+
| Red 2        | 0      | Grey 1       | 2     |
+--------------+--------+--------------+-------+
| Grey 1       | 1      | Green 2      | 0     |
+--------------+--------+--------------+-------+
| Grey 1       | 0      | Grey 1       | 0     |
+--------------+--------+--------------+-------+
| Green 2      | 1      | Green 2      | 1     |
+--------------+--------+--------------+-------+
| Green 2      | 0      | Red 1        | 1     |
+--------------+--------+--------------+-------+
*/
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
#include <avr/io.h>
const int TRANSITION_DELAY = 10;
const int D2 = 1 << PD2;
const int GREEN_LED = 1 << PA0;
const int RED_LED = 1 << PA1;
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
void amberColor
()
{
    do
    {
        PORTA = RED_LED;
        debounce();
        PORTA = GREEN_LED;
    } while (debounce());
}
enum class State
{
    RED,
    AMBER,
    GREEN,
    RED2,
    GREY,
    GREEN2
};
int main()
{
    DDRA = 0xff; 
    DDRD = 0x00;
    State presentState = State::RED;
    while (true)
    {
        debounce();
        switch (presentState)
        {
        case State::RED:
            PORTA = RED_LED;
            if (debounce())
            {
                presentState = State::AMBER;
            }
            break;
        case State::AMBER:
            amberColor
            ();
            presentState = State::GREEN;
            break;
        case State::GREEN:
            PORTA = GREEN_LED;
            if (debounce())
            {
                presentState = State::RED2;
            }
            break;
        case State::RED2:
            PORTA = RED_LED;
            if !(debounce())
            {

                presentState = State::GREY;
            }
            break;
        case State::GREY:
            PORTA = OFF_LED;
            if (debounce())
            {
                presentState = State ::GREEN2;
            }
            break;
        case State ::GREEN2:
            PORTA = GREEN_LED;
            if !debounce()
            {
                presentState = State::RED;
            }
            break;
        }
    }
}
