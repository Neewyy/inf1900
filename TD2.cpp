#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

/*
Tableau
*/

enum class State{ROUGE1, AMBRE_VERT, AMBRE_ROUGE, VERT1, ROUGE2, GRIS1, VERT2};
int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en monde entré

    State presenteState = State::ROUGE1;

    for (;;) //boucle sans fin¨
    {
        switch (presenteState)
        {
            case State::ROUGE1:
                PORTA=(1<<PA1);
                if (PIND & (1 <PD3))
                {
                presenteState=State::AMBREVERT;
                _delay_ms(10);
                }
                break;
            case State::AMBREVERT:
                presenteState=State::AMBRE_ROUGE;
                PORTA=(1<<PA0);
                if (!(PIND & (1 < PD3)))
                {
                    presenteState=State::VERT1;
                    _delay_ms(10);
                }
                break;
            case State::AMBRE_ROUGE:
                presenteState=State::AMBREVERT
                PORTA=(1<<PA1);
                if(!(PIND & (1 < PD3)))
                {
                    presenteState=State::VERT1
                    _delay_ms(10);
                }
                break;
            case State::VERT1:
                PORTA=(1<<PA0);
                if(PIND & (1 <PD3))
                {
                    presenteState=State::ROUGE2
                    _delay_ms(10);
                }
                break;
            case State::ROUGE2:
                PORTA=(1<<PA1);
                if(!(PIND & (1 <PD3)))
                {
                    presenteState=State::GRIS1
                    _delay_ms(10)
                }
                break;
            case State::GRIS1:
                PORTA=0;
                if (PIND & (1 <PD3))
                {
                    presenteState=State::VERT2
                    _delay_ms(10)
                }
                break;
            case State::VERT2:
                PORTA = (1<<PA0);
                if(!(PIND & (1 <PD3)))
                {
                    presenteState=State::ROUGE1
                    _delay_ms(10)
                }
                break;
        }
    }
}
