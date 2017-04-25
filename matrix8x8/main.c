// main.c

#include <avr/io.h>
#include <util/delay.h>
#include "matrix8x8.h"

#include <stdio.h> // na potrzeby testowania
#include "twi.h" // na potrzeby testowania

uint8_t buffer[] = {
	0,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255};

void matrix_test()
{
	const uint8_t addr = 0x71;
	matrix8x8_init(addr);

	// for(int i=0; i<10000; i++)
	// {
	// 	twi_writedata(addr, 0);
	// 	twi_writedata(addr, rand() % 256);
	// }
	matrix8x8_setbrightness(addr, 1);
	_delay_ms(2000);
	matrix8x8_blinkrate(addr, 3);
	_delay_ms(10000);
	matrix8x8_setbrightness(addr, 15);
	_delay_ms(2000);
	matrix8x8_blinkrate(addr, 0);

	//twi_writebuffer(addr, 17, buffer);

}

void led_test()
{
	// nadawanie SOS
	DDRB |= 0b00000001;
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
}

int main(void)
{
	matrix_test();
	led_test();
	for(;;)
	{

	}

  return 0;
}
