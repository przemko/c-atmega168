// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

int main()
{
  clock_prescale_set(clock_div_1);
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
      _delay_ms(2*t);
      
      for(int i=0; i<3; i++)
	{
	  PORTB |= 0b00000001; _delay_ms(t);
	  PORTB &= 0b11111110; _delay_ms(t);
	}
      _delay_ms(6*t);
    }
  return 0;
}

