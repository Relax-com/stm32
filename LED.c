#include "led.h"

void LED_Door_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_DOOR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_DOOR_PORT, &GPIO_InitStructure);

    GPIO_SetBits(LED_DOOR_PORT, LED_DOOR_PIN);
}

void LED_Door_SetState(uint8_t state) {
    if (state) {
        GPIO_ResetBits(LED_DOOR_PORT, LED_DOOR_PIN);
    } else {
        GPIO_SetBits(LED_DOOR_PORT, LED_DOOR_PIN);
    }
}

