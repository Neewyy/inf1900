/*
Travail                                   : TP7 - Librairie
Section #                                 : 03
Equipe #                                  : 6970
Correcteur                                : CORRECTEUR
Noms des auteurs                          : Maiya Sewatari-Mercier, Nicolas Bilodeau, Kevin Trinh-Huynh Minh Tam, Etienne Charbonneau
*/

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class Timer {
public:
	Timer() : timerExpired_(false), timerStarted_(false) {}
	void startTimer1(uint16_t duration);
	void stopTimer1();
	bool getExpired();
	bool getStarted();
	void setExpired();
private:
	bool timerExpired_;
	bool timerStarted_;
};

#endif
