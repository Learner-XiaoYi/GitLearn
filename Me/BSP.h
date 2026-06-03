#ifndef _BSP_H
#define _BSP_H

#include "main.h"
#include "stdio.h"
#include "string.h"

#include "lcd.h"
#include "i2c_hal.h"
#include "usart.h"

#include "system.h"
#include "user.h"

extern int count;
extern int feng;
extern uint16_t key_tick;
extern uint32_t fre;
extern uint32_t dma_buff_1[30];//ADC1 R38
extern uint32_t dma_buff_2[30];//ADC2 R37
extern float adc1;
extern float adc2;



#endif
