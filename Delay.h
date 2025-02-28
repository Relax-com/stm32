#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_init(void);                  // 初始化延时系统
void Delay_us(uint32_t us);             // 微秒延时
void Delay_ms(uint32_t ms);             // 毫秒延时
void Delay_s(uint32_t s);               // 秒延时
uint32_t Delay_ms_GetTick(void);        // 获取当前系统滴答值
uint32_t Delay_ms_Elapsed(uint32_t start);  // 计算从 start 到当前的时间差

#endif
