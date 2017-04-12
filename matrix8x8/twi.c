// twi.c
#include <avr/io.h>
#include <avr/interrupt.h>

#include "twi.h"

void twi_init()
{
  // init TWI ports C4 and C5
  PORTC |= 0b00110000;
  // init TWI prescaler and bitrate
  TWSR |= 0b00000011;
  TWBR = 72; // ((CPU_Speed / TWI_FREQ) - 16) / 2 = 72 czy mniej?
  // enable TWI, acks and interrupt
  TWCR = 0b01000101; // TWEN | TWIE | TWEA
  sei();
}

void twi_writedata(uint8_t addr, uint8_t data)
{

}

void twi_writebuffer(uint8_t addr, int n, uint8_t buffer[])
{

}
