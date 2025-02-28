#include "key.h"
#include "delay.h"

void Key_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    static uint8_t key_up = 1;
    if (key_up && (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0)) {
        Delay_ms(10);
        key_up = 0;
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0) {
            return 1;
        }
    } else if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1) {
        key_up = 1;
    }
    return 0;
}
