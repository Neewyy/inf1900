/*
Travail                                   : TP5 - Probleme 3
Section #                                 : 03
�quipe #                                  : 70
Correcteur                                : CORRECTEUR
Noms des auteurs                          : 
Identifications mat�rielles (Broches I/O) : Entree a D2 ; sorties a PORTA0 et PORTA1.
Description du programme                  : ...
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/eeprom.h>
#include <cstdint>

void initialisationUART() {
    // 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Du USART vers le PC
void transmissionUART(uint8_t donnee) {
    // attendre le buffer d'envoi vide
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = donnee;
}

int main() 
{
    uint16_t adresse = 0x0000;
    uint8_t data;

    initialisationUART();

    while(true) { // or while(1)
        data = eeprom_read_byte((uint8_t*)adresse);
        if (data == 0xFF)
            break;
        transmissionUART(data);
        adresse++;
    }
    return 0;
}