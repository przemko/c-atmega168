// main.c

#include <avr/io.h>
#include <avr/power.h>

int main(void)
{
  clock_prescale_set(clock_div_1);
  uint8_t lfsr = 0x00;
  uint8_t bit0, bit7;
  
  DDRB |= 0b00000001;
  for(;;)
    {
      bit0 = lfsr & 0x01;
      bit7 = ((lfsr&16)<<3)^((lfsr&8)<<4)^((lfsr&4)<<5)^((lfsr&1)<<7);
      bit7 = ~bit7;
      lfsr = (bit7&128)|(lfsr>>1);
      if(bit0)
        PORTB |= 0b00000001;
      else
	PORTB &= 0b11111110;
    }
  return 0;
}
