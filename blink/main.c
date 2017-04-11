#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRB |= (1 << PB0);
    for(;;){
        PORTB = 0b00000001;
        _delay_ms(200);
        PORTB = 0b00000000;
        _delay_ms(500);
    }
    return 0;
}
