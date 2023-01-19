#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
#include <avr/io.h>
const uint16_t TRANSITION_DELAY = 10;
const bool BOUTON = (PIND & 0x04);
const uint16_t GREEN = 1 << PA0;
const uint16_t RED = 1 << PA1;
const uint16_t OFF_LED = 1 << PA2;

/*
+--------------+--------+--------------+-----------+-----------+
| État présent | PIN D2 | État suivant | Sortie A0 | Sortie A1 |
+--------------+--------+--------------+-----------+-----------+
| Up 0         | 0      | Down 1       | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Up 0         | 1      | Up 0         | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Down 1       | 0      | Down 1       | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Down 1       | 1      | Up 1         | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Up 1         | 0      | Down 2       | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Up 1         | 1      | Up 1         | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Down 2       | 0      | Down 2       | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Down 2       | 1      | Up 2         | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Up 2         | 0      | Down 3       | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Up 2         | 1      | Up 2         | 0         | 0         |
+--------------+--------+--------------+-----------+-----------+
| Green        | X      | Up 0         | 1         | 0         |
+--------------+--------+--------------+-----------+-----------+
*/
bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(TRANSITION_DELAY);
        return true;
    }
    return false;
}
enum class State
{
    Up0,
    Up1,
    Down1,
    Down2,
    Up2,
    Green
};
int main()
{

    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en mode entre
                 // le compteur est initialise a 0.
                 // c'est un compteur de 32 bits
    State presentState = State::Up0;

    while (true)
    {
        switch (presentState)
        {
        case State::Up0:
            if (debounce())
            {
                presentState = State ::Down1;
                PORTA = OFF_LED;
            }
            break;
        case State::Down1:
            if (!(debounce()))
            {
                presentState = State ::Up1;
                PORTA = OFF_LED;
            }
            break;
        case State::Up1:
            if (debounce())
            {
                presentState = State ::Down2;
                PORTA = OFF_LED;
            }
            break;
        case State::Down2:
            if (!(debounce()))
            {
                presentState = State ::Up2;
                PORTA = OFF_LED;
            }
            break;
        case State::Up2:
            if (debounce())
            {
                presentState = State ::Green;
                PORTA = OFF_LED;
            }
            break;
        case State::Green:
            presentState = State ::Up0;
            PORTA = GREEN;
            _delay_ms(2000);
            PORTA = OFF_LED;
            break;
        }
    }
    return 0;
}
