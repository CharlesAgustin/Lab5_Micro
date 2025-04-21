#include "Switch.h"

void initSwitch()
{
    DDRD &= ~(1 << DDD3);   // initialize D3 (pin 19) to be input
    PORTD |= (1 << PORTD3); // pull up resistor
    EIMSK |= (1 << INT3);   // Enable INT3 interrupt

    // falling edge interrupt  ISC01=1 ISC00=0
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);
}