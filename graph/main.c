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

	matrix8x8_row(2, 2*(1+4+16+64));
	matrix8x8_writedisplay(addr);

	for(;;)
	{

	}
}

int main(void)
{
  clock_prescale_set(clock_div_1);
	matrix_test();
  return 0;
}
