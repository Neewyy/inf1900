#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
#include <avr/io.h>
const uint16_t TRANSITION_DELAY = 10;
const bool BOUTON = (PIND & 0x04);
const uint16_t GREEN = 1 << PA0;
const uint16_t RED = 1 << PA1;
const uint16_t OFF_LED = 1 << PA2;
/*
+--------------+--------+--------------+-------+
| État présent | PIN D2 | État suivant | PORTA |
+--------------+--------+--------------+-------+
| Rouge 1      | 0      | Rouge 1      | 2     |
+--------------+--------+--------------+-------+
| Rouge 1      | 1      | Ambre Vert   | 2     |
+--------------+--------+--------------+-------+
| Ambre Vert   | 1      | Ambre Rouge  | 1     |
+--------------+--------+--------------+-------+
| Ambre Vert   | 0      | Vert 1       | 1     |
+--------------+--------+--------------+-------+
| Ambre Rouge  | 1      | Ambre Vert   | 2     |
+--------------+--------+--------------+-------+
| Ambre Rouge  | 0      | Vert 1       | 2     |
+--------------+--------+--------------+-------+
| Vert 1       | 1      | Rouge 2      | 1     |
+--------------+--------+--------------+-------+
| Vert 1       | 0      | Vert 1       | 1     |
+--------------+--------+--------------+-------+
| Rouge 2      | 1      | Rouge 2      | 2     |
+--------------+--------+--------------+-------+
| Rouge 2      | 0      | Gris 1       | 2     |
+--------------+--------+--------------+-------+
| Gris 1       | 1      | Vert 2       | 0     |
+--------------+--------+--------------+-------+
| Gris 1       | 0      | Gris 1       | 0     |
+--------------+--------+--------------+-------+
| Vert 2       | 1      | Vert 2       | 1     |
+--------------+--------+--------------+-------+
| Vert 2       | 0      | Rouge 1      | 1     |
+--------------+--------+--------------+-------+
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
void couleurAmbre()
{
    do
    {
        PORTA = RED;
        debounce();
        PORTA = GREEN;
    } while (debounce());
}

enum class State
{
    Rouge1,
    Ambre,
    Vert1,
    Rouge2,
    Gris,
    Vert2
};
int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en monde entré
    State etatPresent = State::Rouge1;
    for (;;) // boucle sans fin¨
    {
        debounce();
        switch (etatPresent)
        {
        case State::Rouge1:
            PORTA = RED;
            if (debounce())
            {
                etatPresent = State::Ambre;
            }
            break;
        case State::Ambre:
            couleurAmbre();
            etatPresent = State::Vert1;
            break;
        case State::Vert1:
            PORTA = GREEN;
            if (debounce())
            {
                etatPresent = State::Rouge2;
            }
            break;
        case State::Rouge2:
            PORTA = RED;
            if (!(debounce()))
            {

                etatPresent = State::Gris;
            }
            break;
        case State::Gris:
            PORTA = OFF_LED;
            if (debounce())
            {
                etatPresent = State ::Vert2;
            }
            break;
        case State ::Vert2:
            PORTA = GREEN;
            if (!debounce())
            {
                etatPresent = State::Rouge1;
            }
            break;
        }
    }
}