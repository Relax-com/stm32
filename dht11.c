#include "dht11.h"
#include "delay.h"

void DHT11_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);

    GPIO_SetBits(DHT11_PORT, DHT11_PIN);
}

uint8_t DHT11_ReadData(uint8_t *temperature, uint8_t *humidity) {
    uint8_t data[5] = {0};
    uint8_t i, j;
    uint32_t timeout;  // 超时计数器

    GPIO_InitTypeDef GPIO_InitStructure;

    // 发送开始信号
    GPIO_ResetBits(DHT11_PORT, DHT11_PIN);
    Delay_ms(18);
    GPIO_SetBits(DHT11_PORT, DHT11_PIN);
    Delay_us(30);

    // 配置为输入模式
    GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);

    // 等待DHT11响应（添加超时）
    timeout = 0;
    while (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {  // 超时100ms
        timeout++;
        Delay_us(1);
    }
    if (timeout >= 100) return 0;  // 超时退出

    timeout = 0;
    while (!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {
        timeout++;
        Delay_us(1);
    }
    if (timeout >= 100) return 0;

    timeout = 0;
    while (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN) && timeout < 100) {
        timeout++;
        Delay_us(1);
    }
    if (timeout >= 100) return 0;

    // 读取40位数据
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            while (!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN));  // 等待低电平
            Delay_us(40);  // 等待高电平
            if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN)) {
                data[i] |= (1 << (7 - j));  // 读取高电平
            }
            while (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN));  // 等待高电平结束
        }
    }

    // 校验数据
    if (data[4] == (data[0] + data[1] + data[2] + data[3])) {
        *humidity = data[0];     // 湿度整数部分
        *temperature = data[2];  // 温度整数部分
        return 1;  // 读取成功
    }

    
    return 0;  // 读取失败
}
