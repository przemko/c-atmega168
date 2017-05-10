// segment7.c

#include <avr/io.h>
#include <twi.h>
#include <segment7.h>

#define HT16K33_CMD_BRIGHTNESS  0xE0
#define HT16K33_BLINK_OFF       0x00
#define HT16K33_BLINK_CMD       0x80
#define HT16K33_BLINK_DISPLAYON 0x01

static const uint8_t digits[16] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

uint16_t display_buffer[8];
uint8_t buffer[33];

void segment7_init(uint8_t addr)
{
  twi_init();
  // turn on oscilator
  twi_writedata(addr, 0x21);
  // set blink and brightness
  segment7_blinkrate(addr, HT16K33_BLINK_OFF);
  segment7_setbrightness(addr, 15);
}

void segment7_blinkrate(uint8_t addr, uint8_t data)
{
  if(data > 3)
    data = 0;
  twi_writedata(addr,	HT16K33_BLINK_CMD |
		HT16K33_BLINK_DISPLAYON |
		(data << 2));
}

void segment7_setbrightness(uint8_t addr, uint8_t data)
{
  if(data > 15)
    data = 15;
  twi_writedata(addr,	HT16K33_CMD_BRIGHTNESS |
		data);
}

void segment7_clear()
{
  for(int i=0; i<8; i++)
    display_buffer[i] = 0;
}


void segment7_writedisplay(uint8_t addr)
{
  buffer[0] = 0x00;
  for(int i=0; i<8; i++)
    {
      buffer[2 * i + 1] = (uint8_t) (display_buffer[i] & 0x00FF);
      buffer[2 * i + 2] = (uint8_t) (display_buffer[i] >> 8);
    }
  twi_writebuffer(addr, 17, buffer);
}

void segment7_writedigitraw(uint8_t d, uint8_t bitmask)
{
  if(d > 4)
    return;
  display_buffer[d] = bitmask;
}

void segment7_writedigitnum(uint8_t d, uint8_t num, bool dot)
{
  if(d > 4)
    return;
  segment7_writedigitraw(d, digits[num] | (dot << 7));
}

void segment7_drawcolon(bool state)
{
  if(state)
    display_buffer[2] = 0x2;
  else
    display_buffer[2] = 0;
}

void segment7_writecolon(uint8_t addr)
{
  uint8_t buf[3] = {0x04, display_buffer[2] & 0xFF, display_buffer[2] >> 8};

  twi_writebuffer(addr, 3, buf);
}
