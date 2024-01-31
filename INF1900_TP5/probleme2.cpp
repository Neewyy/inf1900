/*
Travail                                   : TP5 - Probleme 2
Section #                                 : 03
�quipe #                                  : 
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/


#define F_CPU 8000000

#include <cstdint>
#include <avr/io.h>


// initialisation de l'UART:
void initialisationUART() {
	UBRR0H = 0;
	UBRR0L = 0xCF;
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// transmission d'un octet depuis le USART vers le PC:
void transmissionUART(uint8_t donnee) {
	while (!(UCSR0A & (1 << UDRE0))) {}
	UDR0 = donnee;
}

int main()
{
	// envoi du message "Le robot en INF1900" 100 fois:
	char mots[21] = "Le robot en INF1900\n";
	uint8_t i, j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 20; j++) {
			transmissionUART(mots[j]);
		}
	}

	return 0;
 }