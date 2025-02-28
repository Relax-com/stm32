#ifndef __TIME_H
#define __TIME_H

#include "stm32f10x.h"

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} TimeStruct;

extern volatile TimeStruct currentTime;
extern volatile uint8_t timeEditMode;  // 0:正常 1:小时 2:分钟 3:温度上限 4:湿度上限
extern volatile uint8_t blinkFlag;
extern volatile uint8_t currentTemp;
extern volatile uint8_t currentHumi;
extern volatile uint8_t tempLimit;
extern volatile uint8_t humiLimit;

void TIM3_Init(void);
void Time_Display(void);

#endif
