#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_DOOR_PIN  GPIO_Pin_15
#define LED_DOOR_PORT GPIOC

void LED_Door_Init(void);
void LED_Door_SetState(uint8_t state);

#endif
