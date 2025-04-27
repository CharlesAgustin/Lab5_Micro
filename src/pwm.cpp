#include "pwm.h"
#include "timer.h"
void initBuzzerPin()
{
    DDRE |= (1 << DDE3); // initialize PE3 to be output (pin 5)
}
void initPWMTimer3()
{
    // intialize Fast PWM 10 bit mode TOP 0x3FF
    TCCR3B &= ~(1 << WGM33);               // set WGM3 to 0
    TCCR3A |= (1 << WGM31) | (1 << WGM30); // set WGM1 and WGM0 to 1
    TCCR3B |= (1 << WGM32);                // set WGM2 to 1

    // Set non-inverting mode for OCR3A (clear on compare match, set on bottom)
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    // Set initial duty cycle to 0
    OCR3A = 0;

    TCCR3A |= (1 << COM3A1); // this is written here because if in init buzzer goes off  imidietly
    TCCR3A &= ~(1 << COM3A0);
    // Set presclar to 1 because we want the PWM to be fast, creating constant signal
    TCCR3B |= (1 << CS30);
    TCCR3B &= ~((1 << CS31) | (1 << CS32));
}
void changeDutyCycle(float duty)
{
    OCR3A = 1023 * duty;
}

void turnOffBuzzer()
{
    OCR3A = 0; // turn off the PWM
    PORTE = 0; // Force PE3 low
}

void chirpBuzzer(float duty) // for buzzer to chirp (on, off,on,off)
{
    changeDutyCycle(duty); // make buzzer sound
    delayMs(100);          // give some delay
    changeDutyCycle(0);    // turn off the buzzer sound
    delayMs(100);          // give delay
}