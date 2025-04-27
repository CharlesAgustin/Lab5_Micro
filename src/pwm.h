#ifndef PWM_H
#define PWM_H
#include <avr/io.h>

void initBuzzerPin();
void initPWMTimer3();
void changeDutyCycle(float duty);
void turnOffBuzzer();
void chirpBuzzer(float duty);

#endif
