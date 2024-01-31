/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "PWM.h"


void PWM::initializeTimer2() {
    TCNT2 = 0;
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << WGM22) | (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A) | (1 << OCIE2B);
}

void PWM::initializePWM() {
    initializeTimer2();
    OCR2A = 0;
    OCR2B = 0;
    DDRD |= (1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD5);
}

void PWM::setIntensity(uint8_t leftIntensity, uint8_t rightIntensity) {
    OCR2A = (leftIntensity * 255) / 100;
    OCR2B = (rightIntensity * 255) / 100;
}

void PWM::turnOFF() {
    OCR2A = 0;
    OCR2B = 0;
}