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

  for(;;)
    {
      // nowy waz
    new_snake: ;
      int n = 1;
      int head = 0;
      int tail = 0;
      snake[head].x = 4;
      snake[head].y = 4;
      int dir = 0;
      matrix8x8_clear();
      matrix8x8_drawpixel(snake[head].x, snake[head].y, 1);
      matrix8x8_writedisplay(addr);

      for(;;)
	{
	  
	  // czy sie wydluza?
	  if(n < MAXN && rand()%5 == 0)
	    {
	      int x1 = snake[head].x + (dir==1) - (dir==3);
	      int y1 = snake[head].y + (dir==2) - (dir==0);
	      if(x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8)
		{
		  head++;
		  if(head == MAXN)
		    head = 0;
		  snake[head].x = x1;
		  snake[head].y = y1;
		  matrix8x8_drawpixel(x1, y1, 1);
		  matrix8x8_writedisplay(addr);
		}
	    }

	  
	  _delay_ms(1000);
	}
      
    }

  return 0;
}
