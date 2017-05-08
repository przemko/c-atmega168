// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <segment7.h>
//#include <twi.h> // na czas testowania

int main()
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x70;
  segment7_init(addr);
  segment7_clear();
  segment7_writedisplay(addr);

  uint8_t val[] = {0, 0, 0, 0};

  for(;;)
    {
      segment7_writedigitnum(0, val[0], false);
      segment7_writedigitnum(1, val[1], true);
      segment7_writedigitnum(3, val[2], false);
      segment7_writedigitnum(4, val[3], false);
      segment7_writedisplay(addr);
      int i=3;
      while(i >= 0 && val[i] == 9)
	{
	  val[i] = 0;
	  i--;
	}
      if(i >= 0)
	val[i]++;
      _delay_ms(10);
    }
  return 0;
}

