/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "UART.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *
Nom : initializeUART
Description : Initialise l�UART pour permettre la 
r�ception et la transmission par l�UART0.
* * * * * * * * * * * * * * * * * * * * * * * * */
void UART::initializeUART() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
Nom : transmitUART
Description : Effectue la transmission de donn�es
par l�UART.
* * * * * * * * * * * * * * * * * * * * * * * * */
void UART::transmit(uint8_t data) {
    while (!((UCSR0A) & (1 << UDRE0))) {}
    UDR0 = data; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
Nom : readUART
Description : Permet de lire � partir du UART.
* * * * * * * * * * * * * * * * * * * * * * * * */
uint8_t UART::receive() {
    while(!((UCSR0A) & (1 << RXC0)));
    return UDR0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
Nom : showMemory
Description : Montre la m�moire (en string).
* * * * * * * * * * * * * * * * * * * * * * * * */
void UART::showMemory(char* message){
    for (int i = 0;message[i] != '\0'; i++)
        transmit(message[i]);
}