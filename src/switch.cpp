#include "switch.h"

void initswitch()
{
    DDRD &= ~(1 << DDD3);   // initialize D3 (pin 18) to be input
    PORTD |= (1 << PORTD3); // pull up resistor
    EIMSK |= (1 << INT3);   // Enable INT3 interrupt

    // low level of INT interrupt  ISC01=0 ISC00=0
    EICRA &= ~(1 << ISC31);
    EICRA &= ~(1 << ISC30);
}