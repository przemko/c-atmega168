// segment7.h

#include <stdbool.h>

void segment7_init(uint8_t addr);
void segment7_blinkrate(uint8_t addr, uint8_t data);
void segment7_setbrightness(uint8_t addr, uint8_t data);
void segment7_clear();
void segment7_writedisplay(uint8_t addr);
void segment7_writedigitraw(uint8_t d, uint8_t bitmask);
void segment7_writedigitnum(uint8_t d, uint8_t num, bool dot);
