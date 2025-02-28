#ifndef __TTP_H
#define __TTP_H

#include "stm32f10x.h"

#define TTP223_PIN  GPIO_Pin_7  // 假设TTP223接在PA7
#define TTP223_PORT GPIOA

void TTP223_Init(void);          // 初始化TTP223触摸模块
uint8_t TTP223_ReadState(void);  // 读取触摸状态

#endif
