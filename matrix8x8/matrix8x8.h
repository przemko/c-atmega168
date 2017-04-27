// matrix8x8.h

void matrix8x8_init(uint8_t addr);
void matrix8x8_blinkrate(uint8_t addr, uint8_t data);
void matrix8x8_setbrightness(uint8_t addr, uint8_t data);
void matrix8x8_clear();
void matrix8x8_writedisplay(uint8_t addr);
void matrix8x8_drawpixel(int x, int y, int color);
void matrix8x8_scrolldown();
void matrix8x8_scrollup();
void matrix8x8_row(int i, uint8_t data);
