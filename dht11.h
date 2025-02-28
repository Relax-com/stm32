#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

#define DHT11_PIN  GPIO_Pin_10
#define DHT11_PORT GPIOB

void DHT11_Init(void);
uint8_t DHT11_ReadData(uint8_t *temperature, uint8_t *humidity);

#endif
