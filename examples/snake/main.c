// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdlib.h>
#include <matrix8x8.h>
#include <stdbool.h>

#define MAXN 20

struct point {
  int x, y;
};

struct point snake[MAXN];

int n;
int head;
int tail;

void new_snake(uint8_t addr) {
  n = 1;
  head = 0;
  tail = 0;
  snake[head].x = 4;
  snake[head].y = 4;
  matrix8x8_clear();
  matrix8x8_drawpixel(snake[head].x, snake[head].y, 1);
  matrix8x8_writedisplay(addr);
}

bool free_place(int x1, int y1) {
  if((x1 < 0) || (x1 > 7) || (y1 < 0) || (y1 > 7))
    return false;
  int i = tail;
  for(int j = 0; j < n; j++)
    if((x1 == snake[i].x) && (y1 == snake[i].y))
      return false;
    else {
      i++;
      if(i == MAXN)
	i = 0;
    }
  return true;
}

bool one_step(uint8_t addr) {
  int x1, y1;
  int count = 0;
  do {
    if(count == 16)
      return false;
    int dir = rand() % 4;
    x1 = snake[head].x + (dir==1) - (dir==3);
    y1 = snake[head].y + (dir==2) - (dir==0);
    count++;
  } while(!free_place(x1, y1));
  matrix8x8_drawpixel(x1, y1, 1);
  matrix8x8_writedisplay(addr);
  head++;
  if(head == MAXN)
    head = 0;
  snake[head].x = x1;
  snake[head].y = y1;
  return true;
}

int main()
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x71;
  matrix8x8_init(addr);
  matrix8x8_clear();
  matrix8x8_writedisplay(addr);

  for(;;) {
    new_snake(addr);

    for(;;) {
      if(!one_step(addr))
	break;
      if((rand() % 4) != 0) {
	matrix8x8_drawpixel(snake[tail].x, snake[tail].y, 0);
	matrix8x8_writedisplay(addr);
	tail++;
	if(tail == MAXN)
	  tail = 0;
	n++;
	if(n == MAXN)
	  break;
      }

      _delay_ms(100);
    }
    
  }
  
  return 0;
}
