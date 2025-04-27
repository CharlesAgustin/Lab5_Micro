// Authors: I MADE KENT ABIATAR WIRANATHA, ANDREW LIEMARTA, BARI FAKHRUDIN, CHARLES AGUSTIN
// Net ID: kentabiatar,andrewliemarta,barifakhrudin,charlesagustin
// Date: 15-Apr-2025
// Assignment: Lab 5
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "spi.h"
#include "timer.h"
#include "I2C.h"
#include "pwm.h"
#include "switch.h"

enum button_state
{
  wait_pressed,
  wait_released
};

volatile button_state current_state = wait_pressed; // initial state for button
volatile LED_State initialLED = SMILE;              // state machine for 8x8 LED matrix
volatile bool Buzzer = false;                       // state machine for buzzer
int main()
{
  Serial.begin(9600); // begin serial monitor
  initPWMTimer3();
  initTimer1();
  initMasterSPI();
  initBuzzerPin();
  initI2C();
  initswitch();
  setup_face(initialLED);
  initAccel(); // initialize I2C communication with MPU 6050 accelerometer
  sei();
  int16_t x = 0, y = 0, z = 0;            // variable to store the accelerometer reading
  double x_acc = 0, y_acc = 0, z_acc = 0; // variable to count angle dgeree
  while (1)
  {
    if (current_state != wait_pressed) // make sure button is debounced
    {
      current_state = wait_pressed;
      delayMs(50);
    }
    Read_from(MPU6050_ADDR, ACCEL_XOUT_H); // reading value of x (first half)
    x = Read_data();
    Read_from(MPU6050_ADDR, ACCEL_XOUT_L); // read the value of x (second half)
    x = (x << 8) | Read_data();            // data needs to be shifted to fit second half
    x_acc = (x / 16384.0);                 // normalize the data by deviding with 2^14 (2^14 is the range of Accelerometer)

    Read_from(MPU6050_ADDR, ACCEL_YOUT_H); // reading value of y (first half)
    y = Read_data();
    Read_from(MPU6050_ADDR, ACCEL_YOUT_L); // read the value of y (second half)
    y = (y << 8) | Read_data();            // data needs to be shifted to fit second half
    y_acc = (y / 16384.0);                 // normalize the data by deviding with 2^14 (2^14 is the range of Accelerometer)

    Read_from(MPU6050_ADDR, ACCEL_ZOUT_H); // reading value of z (first half)
    z = Read_data();
    Read_from(MPU6050_ADDR, ACCEL_ZOUT_L); // read the value of z (second half)
    z = (z << 8) | Read_data();            // data needs to be shifted to fit second half
    z_acc = (z / 16384.0);                 // normalize the data by deviding with 2^14 (2^14 is the range of Accelerometer)

    StopI2C_Trans(); // to stop the device from overflowing
    // printing values of the MPU 6050 accelerometer
    Serial.print("x: ");
    Serial.println(x);
    Serial.print(" y: ");
    Serial.println(y);
    Serial.print(" z: ");
    Serial.println(z);

    double roll = atan2(y_acc, sqrt(x_acc * x_acc + z_acc * z_acc));         // count the degree respect to y
    double pitch = atan2(x_acc, sqrt(y_acc * y_acc + z_acc * z_acc)) - 0.12; // count the degree respect to x

    // printing value of degree
    Serial.print("roll: ");
    Serial.println(roll);
    Serial.print("pitch: ");
    Serial.println(pitch);

    if (roll > 0.45 || roll < -0.45 || pitch > 0.45 || pitch < -0.45) // check  if the degree is more than 45 degree or less than -45 degree (45 degree to the other side)
    {
      initialLED = SAD; // make the 8x8 LED matrix to show SAD face
      Buzzer = true;    // change the buzzer state to true (starting the chirping buzzer)
    }
    else
    {
      initialLED = SMILE; // make 8x8 LED matrix to show SMILE face
    }
    if (Buzzer) // check to turn on buzzer
    {
      chirpBuzzer(0.9); // buzzer chirping
    }

    setup_face(initialLED); // show the face (SMILE or SAD)
  }
}

ISR(INT3_vect)
{
  current_state = wait_released; // change the state of button
  turnOffBuzzer();               // turn off the buzzer
  Buzzer = false;                // change the buzzer state to false (stopping the repeat chirping buzzer)
  delayMs(50);                   // debounce the button
}
