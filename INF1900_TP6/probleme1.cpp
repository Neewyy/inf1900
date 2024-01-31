/*
Travail                                   : TP6 - Probleme 1
Section #                                 : 03
Equipe #                                  : 
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications materielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/

// Quand le bouton est enfonce, un compteur qui incremente 10 fois par seconde est active. 
// Quand le bouton est relache ou lorsque le compteur atteint 120, la lumiere clignote vert 
// pendant 1/2 seconde. Ensuite, la carte mere ne fait rien. Puis, deux secondes plus tard, 
// la lumiere rouge s'allume. Elle devra clignoter (compteur / 2) fois au rythme de 2 fois 
// par seconde. Ensuite, la lumiere tourne au vert pendant une seconde. Finalement, 
// elle s'eteint et le robot revient e son etat original.


#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t LED_OFF = 0;
const uint8_t LED_RED = (1 << PB0);
const uint8_t LED_GREEN = (1 << PB1);
volatile uint8_t gCounter = 0;
volatile bool gButtonPressed = false; // buttonPressed initialise a false pq le bouton n'est pas presse au depart

enum class State { INIT, PRESSED, RELEASED, COUNT_120, LED_RED, LED_GREEN };

ISR(TIMER1_COMPA_vect) { // interrupt that increments counter every 100ms (when timer value is at 100 increment)
	gCounter++;
}

ISR(INT0_vect) { // interrupt that checks if button pressed or not
	gButtonPressed = !(PIND & (1 << PD2)); // si le bouton est presse, gButtonPressed devient true
	// debounce
	_delay_ms(5);
}

void initialisation(void) {
	cli();

	DDRB = 0xff;
	DDRD = 0x00;

	EIMSK |= (1 << INT0);

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA
	EICRA |= (1 << ISC00); // for rising edge
	// |= (1 << ISC00) | (1 << ISC01); for falling edge

	sei();
}

void startCounter(uint16_t timerTicks) { // duree = 8Mhz / 1024 = 7812
	gCounter = 0;
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0;
	OCR1A = timerTicks;
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 = (1 << OCIE1A);
}

int main()
{
	uint16_t timerTicks = 781; // 7812 / 10 = 781.2 = 781 ; pour 1000ms, qui a une duree de 7812 cylces, il faut 10 incrementations de gCounter
	initialisation();
	State state = State::INIT;
	int staticCounter = 0;

	//while(true) { switch (state) { ... } }
		// state1 ... when pressed : counter begins (10times per 1000ms)
		// state2 and 3 ... after, if released OR if counter == 120 : green flickering for 500ms, go back to LED_OFF
		// state4 ... 2000ms after LED_OFF : begin LED_RED flickering (2 times per 1000ms) for (counter/2)x
		// state5 ... after flickering for a determined number of times : LED_GREEN on for 1000ms then LED_OFF

	while (true) {
		switch (state) {
		case State::INIT:
			if (PIND & (1 << PD2)) {
				gButtonPressed = true;
				startCounter(timerTicks);
				state = State::PRESSED;
			}
			break;
		case State::PRESSED:
			if (!gButtonPressed && gCounter < 120) {
				cli();
				staticCounter = gCounter;
				state = State::RELEASED;
			}
			else if (gCounter == 120) {
				cli();
				staticCounter = 120;
				state = State::COUNT_120;
			}
			break;
		case State::RELEASED:
		case State::COUNT_120:
			PORTB = LED_GREEN;
			_delay_ms(500);
			PORTB = LED_OFF;
			_delay_ms(2000);
			state = State::LED_RED;
			break;
		case State::LED_RED:
			for (int i = 0; i < staticCounter / 2; i++) {
				PORTB = LED_RED;
				_delay_ms(250);
				PORTB = LED_OFF;
				_delay_ms(250);
			}
			state = State::LED_GREEN;
			break;
		case State::LED_GREEN:
			PORTB = LED_GREEN;
			_delay_ms(1000);
			PORTB = LED_OFF;
			state = State::INIT;
			break;
		}
	}

	return 0;
}