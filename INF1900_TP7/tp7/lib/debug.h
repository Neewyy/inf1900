/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#pragma 
#include "UART.h"
#include "stdio.h"

void print(uint16_t number);
void print(const char* message);

#ifdef DEBUG
#define DEBUG_PRINT(message) print(message)
#else
#define DEBUG_PRINT(message) do {} while(0)
#endif