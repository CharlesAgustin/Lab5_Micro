#include <Arduino.h>
#include <avr/interrupt.h>
#include "spi.h"
#include "timer.h"

enum button_state
{
  wait_pressed,
  wait_released
};

volatile button_state current_state = wait_pressed;
volatile LED_State initialLED = SMILE;
int main()
{
  initMasterSPI();
  setup_face(initialLED);
  sei();

  while (1)
  {
    if (current_state != wait_pressed) // make sure button is debounced
    {
      current_state = wait_pressed;
      delayMs(50);
    }
  }
}

ISR(INT0_vect)
{
  current_state = wait_released; // change the state of button
  delayMs(50);                   // debounce the button
}
