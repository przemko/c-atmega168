// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <matrix8x8.h>
#include <stdlib.h>
#include <stdbool.h>

const uint8_t addr = 0x71;
uint8_t board[8];

bool queens(uint8_t i) {
  if(i > 7) {
    matrix8x8_clear();
    for(uint8_t j = 0; j < 8; j++)
      matrix8x8_drawpixel(j, board[j], 1);
    matrix8x8_writedisplay(addr);
    _delay_ms(100);
    return false; // powinno byc true ale false wymusi dalsze szukanie
  }
  else {
    for(uint8_t k = 0; k < 8; k++) {
      bool cont = true;
      for(uint8_t j = 0; cont && j < i; j++) 
	if(board[j] == k || abs(board[j] - k) == i - j)
	  cont = false;
      if(cont) {
	board[i] = k;
	if(queens(i+1))
	  return true;
      }
    }
    return false;
  }
}

int main()
{
  clock_prescale_set(clock_div_1);
  matrix8x8_init(addr);
  matrix8x8_clear();
  matrix8x8_writedisplay(addr);
  while(1) {
    queens(0);
  }
  return 0;
}
