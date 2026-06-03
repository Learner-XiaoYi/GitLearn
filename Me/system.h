#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "BSP.h"

void system_init(void);
void adc_show(void);
void eeprom_write(uint8_t addr,uint8_t dat);
uint8_t eeprom_read(uint8_t addr);

#endif
