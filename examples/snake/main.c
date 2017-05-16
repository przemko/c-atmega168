// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdlib.h>
#include <matrix8x8.h>

#define MAXN 20

int main()
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x71;
  matrix8x8_init(addr);
  matrix8x8_clear();
  matrix8x8_writedisplay(addr);

  struct point {
    int x, y;
  };

  struct point snake[MAXN];
  int n = 1;
  int first = 0;
  int last = 0;
  snake[first].x = 4;
  snake[first].y = 4;
  int dir = 0;

  // wyswietl weza
  matrix8x8_drawpixel(snake[first].x, snake[first].y, 1);
  matrix8x8_writedisplay(addr);

  for(;;)
    {
      

    }

  return 0;
}
