/*
Travail                                   : TP5 - Probleme 1
Section #                                 : 03
�quipe #                                  : 
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier et Nicolas Bilodeau
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <cstdint>
#include <string>
using namespace std;

#define LED_GREEN (1 << PB0)
#define LED_RED (1 << PB1)
#define BASE_ADDRESS 0x0000

int main()
{
	DDRC = LED_GREEN | LED_RED;
	PORTC = 0x00;
	string STRING = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0"

		char* string_ptr = &STRING[0]; // points to the first character of STRING
	uint16_t* memory_ptr = (uint16_t*)BASE_ADDRESS; // & is not used so does not point to the addr of a local variable BUT to the specific memory location given by BASE_ADDRESS

	// Write string to memory
	for (int i = 0; i < STRING.length(); i++) {
		*memory_ptr = STRING[i];
		memory_ptr++;
		_delay_ms(5);
	}

	// Read string from memory
	//memory_ptr = (uint16_t*)BASE_ADDRESS;
	//string_ptr = &STRING[0];
	int match_count = 0;
	for (int i = 0; i < STRING.length(); i++) {
		if (*memory_ptr != STRING[i]) {
			PORTB = LED_RED;
			match_count++;
		}
		else
			PORTB = LED_GREEN;
		_delay_ms(5);
		memory_ptr++;
	}
	
	if (match_count > 0) {
		PORTB = LED_RED;
		_delay_ms(3000);
	}
	else {
		PORTB = LED_GREEN;
		_delay_ms(3000);
	}
	
	return 0;
}