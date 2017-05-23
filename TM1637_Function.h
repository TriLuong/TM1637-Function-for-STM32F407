#ifndef __TM1637_Function_
#include "stm32f4xx_hal.h"

void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_Write(unsigned char Data);
void TM1637_disPlay(unsigned char value, unsigned led_pos, unsigned char led_status, unsigned char led_brightness);

#endif