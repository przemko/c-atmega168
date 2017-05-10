// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdbool.h>
#include <segment7.h>

int main()
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x70;
  segment7_init(addr);
  segment7_clear();
  segment7_writedisplay(addr);

  uint8_t val[] = {0, 0, 0, 0};
  segment7_writedigitnum(0, val[0], false);
  segment7_writedigitnum(1, val[1], false);
  segment7_writedigitnum(3, val[2], false);
  segment7_writedigitnum(4, val[3], false);
  segment7_writedisplay(addr);

  bool state = true;
  uint8_t seconds = 0;

  for(;;)
    {

      segment7_drawcolon(state);
      segment7_writecolon(addr);
      state = !state;
      seconds++;
      if(seconds == 60)
      {
        seconds = 0;
        if(val[3] == 9)
        {
          val[3] = 0;
          if(val[2] == 5)
          {
            val[2] = 0;
            if(val[1] == 9)
            {
              val[1] = 0;
              if(val[0] == 9)
              {
                val[0] = 0;
              }
              else
                val[0]++;
            }
            else
              val[1]++;
          }
          else
            val[2]++;
        }
        else
          val[3]++;
        segment7_writedigitnum(0, val[0], false);
        segment7_writedigitnum(1, val[1], false);
        segment7_writedigitnum(3, val[2], false);
        segment7_writedigitnum(4, val[3], false);
        segment7_writedisplay(addr);
      }
      _delay_ms(1000);
    }
  return 0;
}
