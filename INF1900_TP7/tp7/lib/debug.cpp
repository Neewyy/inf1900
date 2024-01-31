/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include <debug.h>
UART debugUART;

void print(uint16_t number) {
    char buff[5];
    snprintf(buff, 5, "%d", number);
    print(buff);
}

void print(const char* message) {
    debugUART.initializeUART();
    uint16_t i = 0;
    while (message[i] != '\0')
        debugUART.transmit(message[i++]);
}