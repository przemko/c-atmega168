// twi.h

void twi_init();
void twi_writedata(uint8_t addr, uint8_t data);
void twi_writebuffer(uint8_t addr, int n, uint8_t buffer[]);

