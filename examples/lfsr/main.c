// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include "matrix8x8.h"

int main(void)
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x71;
  matrix8x8_init(addr);
  matrix8x8_clear();
  
  uint8_t lfsr = 0x00;
  uint8_t bit0, bit7;
  
  DDRB |= 0b00000001;
  for(;;)
    {
      bit0 = lfsr & 0x01;
      bit7 = ((lfsr&16)<<3)^((lfsr&8)<<4)^((lfsr&4)<<5)^((lfsr&1)<<7);
      bit7 = ~bit7;
      lfsr = (bit7&128)|(lfsr>>1);
      matrix8x8_scrolldown();
      matrix8x8_row(0, lfsr);
      matrix8x8_writedisplay(addr);
      PORTB |= bit0;
      _delay_ms(80);
      PORTB &= 0b11111110;
      _delay_ms(20);
    }
  return 0;
}
