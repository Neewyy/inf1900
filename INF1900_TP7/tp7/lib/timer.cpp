/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#include "timer.h"


void Timer::startTimer1(uint16_t duration) {
	TCNT1 = 0;
	OCR1A = duration;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
	
	timerExpired_ = false;
	timerStarted_ = true;
}

void Timer::stopTimer1() {
	TIMSK1 |= (0 << OCIE1A);
}

bool Timer::getExpired() {
	return timerExpired_;
}

bool Timer::getStarted() {
	return timerStarted_;
}

void Timer::setExpired() {
	timerExpired_ = true;
}