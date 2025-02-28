#include "ttp.h"
#include "delay.h"

// 初始化TTP223触摸模块
void TTP223_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 启用GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置TTP223引脚为输入模式
    GPIO_InitStructure.GPIO_Pin = TTP223_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TTP223_PORT, &GPIO_InitStructure);
}

// 读取触摸状态
uint8_t TTP223_ReadState(void) {
    if (GPIO_ReadInputDataBit(TTP223_PORT, TTP223_PIN)) {
        Delay_ms(10);  // 消抖
        if (GPIO_ReadInputDataBit(TTP223_PORT, TTP223_PIN)) {
            return 1;  // 触摸按下
        }
    }
    return 0;  // 未触摸
}
