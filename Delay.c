#include "delay.h"

static uint32_t tick = 0;  // 全局滴答计数器

// 初始化延时系统（配置 SysTick 定时器）
void Delay_init(void) {
    // 配置 SysTick 定时器为 1ms 中断一次
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);  // 初始化失败，死循环
    }
}

// SysTick 中断服务函数
void SysTick_Handler(void) {
    tick++;  // 每 1ms 增加一次
}

// 微秒延时
void Delay_us(uint32_t us) {
    uint32_t start = tick;
    while (tick - start < us / 1000);
}

// 毫秒延时
void Delay_ms(uint32_t ms) {
    uint32_t start = tick;
    while (tick - start < ms);
}

// 秒延时
void Delay_s(uint32_t s) {
    Delay_ms(s * 1000);
}

// 获取当前系统滴答值
uint32_t Delay_ms_GetTick(void) {
    return tick;
}

// 计算从 start 到当前的时间差
uint32_t Delay_ms_Elapsed(uint32_t start) {
    return tick - start;
}
