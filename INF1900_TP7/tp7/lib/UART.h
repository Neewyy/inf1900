/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef UART_H
#define UART_H

#include "memoire_24.h"


class UART{
public:
    UART();
    void initializeUART();
    void transmit(uint8_t data);
    uint8_t receive(); 
    void showMemory(char* message);
};

#endif