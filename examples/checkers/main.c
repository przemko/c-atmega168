// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <matrix8x8.h>
#include <stdlib.h>

const uint8_t addr = 0x71;

char board[8][8];

void init_board(void) {
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      board[i][j] = 0;

  for(int i = 0; i < 3; i++)
    for(int j = i % 2; j < 8; j += 2)
      board[i][j] = 2;

  for(int i = 5; i < 8; i++)
    for(int j = (i % 2); j < 8; j += 2)
      board[i][j] = 1;
}

void clear_screen(void) {
  matrix8x8_clear();
  matrix8x8_writedisplay(addr);
}

ISR(TIMER1_COMPA_vect) {
  matrix8x8_clear();
  for(int i = 0; i<8; i++)
    for(int j=0; j<8; j++)
      if(board[i][j] == 1)
	matrix8x8_drawpixel(i, j, 1);
  sei();
  matrix8x8_writedisplay(addr);
  cli();

   _delay_ms(2);
   
  for(int i=0; i<8; i++)
    for(int j = 0; j<8; j++)
      if(board[i][j] == 2)
	matrix8x8_drawpixel(i, j, 1);
  sei();
  matrix8x8_writedisplay(addr);
  cli();
}

int main(void) {
  DDRB |= 0b00000001;

  init_board();
  
  matrix8x8_init(addr);
  clear_screen();
  matrix8x8_writedisplay(addr);

  
  OCR1A = 0x0060; // co najmniej 0x0020
  TCCR1B |= (1 << WGM12); // Mode 4, CTC on OCR1A
  TIMSK1 |= (1 << OCIE1A); //Set interrupt on compare match
  TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
  sei(); // enable interrupts

  
  while(1) {
  }
  return 0;
}
