// main.c

#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect) {
  PORTB |= 0b00000001; 
  _delay_ms(10);
  PORTB &= 0b11111110;
}

int main(void) {
  DDRB |= 0b00000001;
  OCR1A = 0x0200;
  TCCR1B |= (1 << WGM12);
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  sei();

  
  while(1) {
  }
  return 0;
}
