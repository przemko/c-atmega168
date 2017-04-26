// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include "matrix8x8.h"

void matrix_test()
{
	const uint8_t addr = 0x71;
	matrix8x8_init(addr);
	matrix8x8_clear();
	matrix8x8_writedisplay(addr);
	for(;;)
	{
		for(int i=4; i<8; i++)
		{
			for(int j=4; j<=i; j++)
			{
				matrix8x8_drawpixel(7-i, 7-i, 1);
				matrix8x8_drawpixel(7-i, i, 1);
				matrix8x8_drawpixel(i, 7-i, 1);
				matrix8x8_drawpixel(i, i, 1);
			}
			matrix8x8_writedisplay(addr);
			_delay_ms(80);
		}
		for(int i=4; i<8; i++)
		{
			for(int j=4; j<8; j++)
			{
				matrix8x8_drawpixel(7-i, 7-i, 0);
				matrix8x8_drawpixel(7-i, i, 0);
				matrix8x8_drawpixel(i, 7-i, 0);
				matrix8x8_drawpixel(i, i, 0);
			}
			matrix8x8_writedisplay(addr);
			_delay_ms(80);
		}
	}
}

int main(void)
{
  clock_prescale_set(clock_div_1);
	matrix_test();
  return 0;
}
