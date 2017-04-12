// matrix8x8.c

#include <avr/io.h>
#include "twi.h"
#include "matrix8x8.h"

#define HT16K33_CMD_BRIGHTNESS  0xE0
#define HT16K33_BLINK_OFF       0x00
#define HT16K33_BLINK_CMD       0x80
#define HT16K33_BLINK_DISPLAYON 0x01

uint16_t display_buffer[8];
uint8_t buffer[33];

void matrix8x8_init(uint8_t addr)
{
	twi_init();
	// turn on oscilator
	twi_writedata(addr, 0x21);
	// set blink and brightness
	matrix8x8_blinkrate(addr, HT16K33_BLINK_OFF);
	matrix8x8_setbrightness(addr, 15);
}

void matrix8x8_blinkrate(uint8_t addr, uint8_t data)
{
	if(data > 3)
		data = 0;
	twi_writedata(addr,	HT16K33_BLINK_CMD |
						HT16K33_BLINK_DISPLAYON |
						(data << 2));
}
void matrix8x8_setbrightness(uint8_t addr, uint8_t data)
{
	if(data > 15)
		data = 15;
	twi_writedata(addr,	HT16K33_CMD_BRIGHTNESS |
						data);
}

void matrix8x8_clear()
{
	for(int i=0; i<8; i++)
		display_buffer[i] = 0;
}

void matrix8x8_writedisplay(uint8_t addr)
{
	buffer[0] = 0x00;
	for(int i=0; i<8; i++)
	{
		buffer[2 * i + 1] = (uint8_t) (display_buffer[i] & 0x00FF);
		buffer[2 * i + 2] = (uint8_t) (display_buffer[i] >> 8);
	}
	twi_writebuffer(addr, 17, buffer);
}

void matrix8x8_drawpixel(int x, int y, int color)
{
	if(y < 0 || y >= 8 || x < 0 || x >= 8)
		return;
	x += 7;
	x %= 8;
	if(color)
		display_buffer[y] |= (1 << x);
	else
		display_buffer[y] &= ~(1 << x);
}
