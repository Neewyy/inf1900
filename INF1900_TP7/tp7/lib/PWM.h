/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class PWM {
public:
    PWM();
    void initializeTimer2();
    void initializePWM();
    void setIntensity(uint8_t leftIntensity, uint8_t rightIntensity);
    void turnOFF();
};

#endif