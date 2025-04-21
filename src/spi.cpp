#include "spi.h"
#include "string.h"
#define DDR_SPI DDRB
#define CS_PIN PB0
#define DD_SCK DDB1
#define DD_MOSI DDB2

#define SPI_PORT PORTB
#define SPI_SS_BIT PORTB0

void initMasterSPI()
{
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << CS_PIN);
    SPI_PORT |= (1 << SPI_SS_BIT);
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << SPR1) | (1 << SPR0);
}

void spi_send_byte(uint8_t data)
{
    SPDR = data; // Start the transmission by writing to the SPI Data Register
    while (!(SPSR & (1 << SPIF)))
        ; // Wait until the SPI transfer is complete
}

void max7219_send_data(uint8_t address, uint8_t data)
{
    PORTB &= ~(1 << CS_PIN); // Set CS low (start communication)
    spi_send_byte(address);  // Send address to the MAX7219
    spi_send_byte(data);     // Send data to the MAX7219
    PORTB |= (1 << CS_PIN);  // Set CS high (end communication)
}

void setup_face(LED_State current_LED_state)
{
    max7219_send_data(0x0F, 0x00); // Display test off
    max7219_send_data(0x0C, 0x01); // Shutdown mode off
    max7219_send_data(0x0B, 0x07); // Scan all 8 digits
    max7219_send_data(0x09, 0x00); // No decode
    max7219_send_data(0x0A, 0x01); // Max intensity

    uint8_t smiley[8];
    switch (current_LED_state)
    {
    case SMILE:
        uint8_t happy[8] = {0x00, 0x66, 0x66, 0x00, 0x81, 0x42, 0x3C, 0x00};
        memcpy(smiley, happy, 8);
        break;

    case SAD:
        uint8_t sad[8] = {0x00, 0x66, 0x66, 0x00, 0x3C, 0x42, 0x81, 0x00};
        memcpy(smiley, sad, 8);
        break;
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        max7219_send_data(i + 1, smiley[i]);
    }
}