// twi.h
//
// Na podstawie I2C package for AVR-Ada by Tero Koskinen.

#include <stdbool.h>

#define TWI_FREQ   100000
#define CPU_SPEED 8000000

enum TWI_Error_Enum {
  TWI_No_Error,
  TWI_Bus_Error,
  TWI_Lost_Arbitration,
  TWI_NACK
};

void twi_init();
void twi_requestdata(uint8_t addr, int amount);
bool twi_dataavailable();
uint8_t twi_receive();
void twi_writedata(uint8_t addr, uint8_t data);
void twi_writebuffer(uint8_t addr, int n, uint8_t data[]);
enum TWI_Error_Enum twi_geterror();
