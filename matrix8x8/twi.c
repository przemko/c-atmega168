// twi.c
//
// Na podstawie I2C package for AVR-Ada by Tero Koskinen.

#include <avr/io.h>
#include <avr/interrupt.h>

#include "twi.h"

enum TWI_State_Enum {
    TWI_Ready,
    TWI_MRX,
    TWI_MTX
};

volatile enum TWI_Error_Enum TWI_Error_State;

#define TW_READ  1
#define TW_WRITE 0

#define TW_START        0x08
#define TW_REP_START    0x10

#define TW_MT_SLA_ACK   0x18
#define TW_MT_SLA_NACK  0x20

#define TW_MT_DATA_ACK  0x28
#define TW_MT_DATA_NACK 0x30

#define TW_MR_SLA_ACK   0x40
#define TW_MR_SLA_NACK  0x48

#define TW_MR_DATA_ACK  0x50
#define TW_MR_DATA_NACK 0x58

#define TW_BUS_ERROR  0x00
#define TW_NO_INFO    0xF8
#define TW_ARB_LOST   0x38

uint8_t buffer[33];

int data_index;
int data_max;
int data_received;
bool data_sent;

volatile enum TWI_State_Enum TWI_State;
volatile uint8_t TWI_SLA_RW;

void stop();
void reply(bool ack);
void release();

void twi_init()
{
  data_index = 1;
  data_max = 1;
  data_sent = false;
  TWI_State = TWI_Ready;

  // init TWI ports C4 and C5
  PORTC |= 0b00110000;
  // init TWI prescaler and bitrate
  TWSR &= ~0b00000011;
  TWBR = 5; // ((CPU_Speed / TWI_FREQ) - 16) / 2 czy nie odejmowac 16?
  // enable TWI, acks and interrupt
  TWCR = 0b01000101; // TWEN | TWIE | TWEA
  sei();
}

void twi_requestdata(uint8_t addr, int amount)
{
  data_index = 1;
  data_max = amount;
  data_received = 0;
  TWI_Error_State = TWI_No_Error;
  TWI_State = TWI_MRX;
  TWI_SLA_RW = TW_READ | (addr << 1);
  TWCR = 0b11100101; // TWEN | TWIE | TWEA | TWINT | TWSTA

  while(TWI_State == TWI_MRX);

}

bool twi_dataavailable()
{
  return data_index <= data_received;
}

uint8_t twi_receive()
{
  uint8_t ret_val = 0;
  if(data_index <= data_received)
  {
    ret_val = buffer[data_index];
    data_index++;
  }
  return ret_val;
}

void twi_writedata(uint8_t addr, uint8_t data)
{
  data_sent = false;
  buffer[1] = data;
  data_index = 1;
  data_max = data_index;

  TWI_State = TWI_MTX;
  TWI_Error_State = TWI_No_Error;

  TWI_SLA_RW = TW_WRITE | (addr << 1);

  TWCR = 0b11100101; // TWEN | TWIE | TWEA | TWINT | TWSTA

  while(TWI_State == TWI_MTX);

}

void twi_writebuffer(uint8_t addr, int n, uint8_t data[])
{
  int index = 1;
  data_sent = false;
  for(int i=0; i<n; i++)
  {
    buffer[index] = data[i];
    index++;
  }
  data_index = 1;
  data_max = index - 1;

  TWI_State = TWI_MTX;
  TWI_Error_State = TWI_No_Error;

  TWI_SLA_RW = TW_WRITE | (addr << 1);

  TWCR = 0b11100101; // TWEN | TWIE | TWEA | TWINT | TWSTA

  while(TWI_State == TWI_MTX);
}

void stop()
{
  TWCR = 0b11010101; // TWEN | TWIE | TWEA | TWINT | TWSTO
  while(TWCR & 0b00010000);
  TWI_State = TWI_Ready;
}

void reply(bool ack)
{
  if(ack)
    TWCR = 0b11000101;
  else
    TWCR = 0b10000101;
}

void release()
{
  TWCR = 0b11000101;
  TWI_State = TWI_Ready;
}

ISR(TWI_vect)
{
  const uint8_t TW_Status_Mask = 0b11111000;
  const uint8_t TW_Status = TWSR & TW_Status_Mask;
  switch(TW_Status)
  {
    case TW_START:
    case TW_REP_START:
      TWDR = TWI_SLA_RW;
      reply(true);
      break;
    case TW_ARB_LOST:
      TWI_Error_State = TWI_Lost_Arbitration;
      release();
      break;
    case TW_MR_SLA_ACK:
      if(data_received < data_max - 1)
        reply(true);
      else
        reply(false);
      break;
    case TW_MR_SLA_NACK:
      stop();
      break;
    case TW_MR_DATA_ACK:
      buffer[data_received + 1] = TWDR;
      data_received++;
      if(data_received < data_max)
        reply(true);
      else
        reply(false);
      break;
    case TW_MR_DATA_NACK:
      buffer[data_received + 1] = TWDR;
      data_received++;
      stop();
      break;
    case TW_MT_SLA_ACK:
    case TW_MT_DATA_ACK:
      if(data_index <= data_max && !data_sent)
      {
        TWDR = buffer[data_index];
        if(data_index < data_max)
          data_index++;
        else
          data_sent = true;
        reply(true);
      }
      else
        stop();
      break;
    case TW_MT_SLA_NACK:
    case TW_MT_DATA_NACK:
      TWI_Error_State = TWI_NACK;
      stop();
      break;
  }
}
enum TWI_Error_Enum twi_geterror()
{
  return TWI_Error_State;
}
