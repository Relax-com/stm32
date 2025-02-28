#include "time.h"
#include "oled.h"
#include "delay.h"

volatile TimeStruct currentTime = {12, 0, 0};
volatile uint8_t timeEditMode = 0;
volatile uint8_t blinkFlag = 0;
volatile uint8_t currentTemp = 0;
volatile uint8_t currentHumi = 0;
volatile uint8_t tempLimit = 30;
volatile uint8_t humiLimit = 70;

void TIM3_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 7199;
    TIM_TimeBaseStructure.TIM_Prescaler = 9999;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void) {
    static uint32_t counter = 0;
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        
        if (++counter >= 1) {
            counter = 0;
            if (timeEditMode == 0) {
                if (++currentTime.seconds >= 60) {
                    currentTime.seconds = 0;
                    if (++currentTime.minutes >= 60) {
                        currentTime.minutes = 0;
                        currentTime.hours = (currentTime.hours + 1) % 24;
                    }
                }
            }
            if (timeEditMode != 0) {
                blinkFlag ^= 1;
            }
        }
    }
}


// 新增湿度限值闪烁显示逻辑
void Time_Display(void) {
    OLED_Clear();

    // 时间显示
    OLED_ShowString(1, 1, "Time:");
    if(timeEditMode == 1 && blinkFlag) {
        OLED_ShowString(1, 6, "  ");
    } else {
        OLED_ShowNum(1, 6, currentTime.hours, 2);
    }
    OLED_ShowString(1, 8, ":");
    if(timeEditMode == 2 && blinkFlag) {
        OLED_ShowString(1, 9, "  ");
    } else {
        OLED_ShowNum(1, 9, currentTime.minutes, 2);
    }

    // 温湿度显示
    OLED_ShowString(3, 1, "Temp:");
    if(timeEditMode == 3 && blinkFlag) {
        OLED_ShowString(3, 6, "  ");
    } else {
        OLED_ShowNum(3, 6, currentTemp, 2);
    }
    OLED_ShowString(3, 9, "C");

    OLED_ShowString(4, 1, "Humi:");
    if(timeEditMode == 4 && blinkFlag) {  // 新增湿度限值闪烁
        OLED_ShowString(4, 6, "  ");
    } else {
        OLED_ShowNum(4, 6, currentHumi, 2);
    }
    OLED_ShowString(4, 9, "%");

    // 限值显示
    OLED_ShowString(2, 1, "Limit:");
    OLED_ShowNum(2, 7, tempLimit, 2);
    OLED_ShowString(2, 9, "C/");
    OLED_ShowNum(2, 12, humiLimit, 2);  // 显示湿度限值
    OLED_ShowString(2, 14, "%");
}
