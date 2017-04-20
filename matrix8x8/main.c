// main.c

#include <avr/io.h>
#include <util/delay.h>
#include "matrix8x8.h"

int main(void)
{
	const uint8_t addr = 0x71;
	matrix8x8_init(addr);

	// inicjowanie D0
	DDRB |= 0b00000001;
	// nadawanie SOS
	int t = 1200 / 20; // 1200 ms / words per minute
	for(;;)
	{
		for(int i=0; i<3; i++)
		{
			PORTB |= 0b00000001; _delay_ms(t);
			PORTB &= 0b11111110; _delay_ms(t);
		}
		_delay_ms(2*t);

		for(int i=0; i<3; i++)
		{
			PORTB |= 0b00000001; _delay_ms(3*t);
			PORTB &= 0b11111110; _delay_ms(t);
		}
		_delay_ms(t);

		for(int i=0; i<3; i++)
		{
			PORTB |= 0b00000001; _delay_ms(t);
			PORTB &= 0b11111110; _delay_ms(t);
		}
		_delay_ms(6*t);
	}

    return 0;
}
