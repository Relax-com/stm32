#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY1_PIN  GPIO_Pin_4
#define KEY2_PIN  GPIO_Pin_5
#define KEY3_PIN  GPIO_Pin_6
#define KEY_PORT  GPIOA

void Key_Init(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
