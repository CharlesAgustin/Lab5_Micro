#ifndef SPI_H
#define SPI_H
#include <avr/io.h>
enum LED_State
{
    SMILE,
    SAD
};

void initMasterSPI();
void spi_send_byte(uint8_t data);
void max7219_send_data(uint8_t address, uint8_t data);
void setup_face(LED_State current_LED_state);
#endif