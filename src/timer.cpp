#include "timer.h"
// Initialize timer 1
// Use CTC mode
void initTimer1()
{
    // intialize  CTC mode = 0100
    TCCR1B &= (1 << WGM13);  // set WGM3 to 0
    TCCR1B |= (1 << WGM12);  // set WGM2 to 1
    TCCR1A &= ~(1 << WGM11); // set WGM1 to 0
    TCCR1A &= ~(1 << WGM10); // set WGM0 to 0

    // initialze prescalar of 8 (CS = 010  )
    TCCR1B &= ~(1 << CS12) | (1 << CS10); // set CS12 and CS10 to be 0
    TCCR1B |= (1 << CS11);                // set CS11 to be 1
}

void delayMs(unsigned int delay)
{
    int prescalar = 8;                            // set the value of prescalar 1024 to calculate
    OCR1A = ((0.001 * 16000000) / prescalar) - 1; // 1999 tick for 1 milisecond
    for (unsigned int i = 0; i < delay; i++)      // keep on counting until reach the disered value of delay
    {
        TCNT1 = 0; // reset timer counter
        while (!(TIFR1 & (1 << OCF1A)))
            ;                  // do nothing when flag is down
        TIFR1 |= (1 << OCF1A); // set the flag down
    }
}