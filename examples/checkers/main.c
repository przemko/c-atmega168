// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <matrix8x8.h>
#include <stdlib.h>

const uint8_t addr = 0x71;

char board[8][8];

uint8_t wh_0, wh_1, wh_2, wh_3, wh_4, wh_5, wh_6, wh_7;
uint8_t bl_0, bl_1, bl_2, bl_3, bl_4, bl_5, bl_6, bl_7;

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

  bl_0 = 0b10101010;
  bl_1 = 0b01010101;
  bl_2 = 0b10101010;
  bl_3 = 0b00000000;
  bl_4 = 0b00000000;
  bl_5 = 0b00000000;
  bl_6 = 0b00000000;
  bl_7 = 0b00000000;

  wh_0 = 0b00000000;
  wh_1 = 0b00000000;
  wh_2 = 0b00000000;
  wh_3 = 0b00000000;
  wh_4 = 0b00000000;
  wh_5 = 0b01010101;
  wh_6 = 0b10101010;
  wh_7 = 0b01010101;
}

void clear_screen(void) {
  matrix8x8_clear();
  matrix8x8_writedisplay(addr);
}

ISR(TIMER1_COMPA_vect) {

  matrix8x8_row(0, wh_0);
  matrix8x8_row(1, wh_1);
  matrix8x8_row(2, wh_2);
  matrix8x8_row(3, wh_3);
  matrix8x8_row(4, wh_4);
  matrix8x8_row(5, wh_5);
  matrix8x8_row(6, wh_6);
  matrix8x8_row(7, wh_7);
  
  sei();
  matrix8x8_writedisplay(addr);
  cli();

  _delay_ms(1);
  matrix8x8_row(0, wh_0 | bl_0);
  matrix8x8_row(1, wh_1 | bl_1);
  matrix8x8_row(2, wh_2 | bl_2);
  matrix8x8_row(3, wh_3 | bl_3);
  matrix8x8_row(4, wh_4 | bl_4);
  matrix8x8_row(5, wh_5 | bl_5);
  matrix8x8_row(6, wh_6 | bl_6);
  matrix8x8_row(7, wh_7 | bl_7);
  
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
    _delay_ms(25);
    bl_3 = bl_2 >> 1;
    bl_2 = 0b00000000;
    _delay_ms(25);
    bl_2 = bl_3 << 1;
    bl_3 = 0b00000000;

  }
  return 0;
}