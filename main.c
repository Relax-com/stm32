#include "stm32f10x.h"
#include "oled.h"
#include "key.h"
#include "time.h"
#include "delay.h"
#include "ttp.h"
#include "led.h"
#include "dht11.h"

int main(void) {
	
    // 初始化系统
    SystemInit();
    Delay_init();  // 初始化延时函数
    OLED_Init();
    OLED_ShowString(1, 1, "OLED INIT OK");  // 调试信息：OLED 初始化成功
    Delay_ms(1000);
    OLED_Clear();

    Key_Init();
    TIM3_Init();
    TTP223_Init();
    LED_Door_Init();
    DHT11_Init();

    __enable_irq();

    uint8_t doorState = 0;  // 柜门状态
    uint8_t temperature = 0, humidity = 0;  // 温湿度数据
    uint32_t lastDHT11ReadTime = 0;  // 上次读取DHT11的时间

    while (1) {
        // 检测TTP223触摸
        if (TTP223_ReadState()) {
            Delay_ms(50);  // 消抖
            if (TTP223_ReadState()) {
                doorState = !doorState;  // 切换柜门状态
                LED_Door_SetState(doorState);  // 更新柜门状态LED
                while (TTP223_ReadState());  // 等待触摸释放
                OLED_ShowString(5, 1, "TTP OK ");  // 调试信息：触摸成功
            }
        }

        // 每隔1秒读取一次DHT11数据
        if (Delay_ms_Elapsed(lastDHT11ReadTime) >= 1000) {  // 1秒间隔
            if (DHT11_ReadData(&temperature, &humidity)) {
                currentTemp = temperature;
                currentHumi = humidity;
                OLED_ShowString(4, 1, "DHT11 OK ");  // 调试信息：读取成功
            } else {
                OLED_ShowString(4, 1, "DHT11 ERR");  // 调试信息：读取失败
            }
            lastDHT11ReadTime = Delay_ms_GetTick();  // 更新上次读取时间
        }

        // 按键1：模式切换
    if(Key_Scan(KEY_PORT, KEY1_PIN)) {
        timeEditMode = (timeEditMode + 1) % 5;  // 0-4循环
        blinkFlag = 0;
    }

    // 按键2：增加值
    if(Key_Scan(KEY_PORT, KEY2_PIN)) {
        switch(timeEditMode) {
            case 1:  // 小时
                currentTime.hours = (currentTime.hours + 1) % 24;
                break;
            case 2:  // 分钟
                currentTime.minutes = (currentTime.minutes + 1) % 60;
                break;
            case 3:  // 温度上限
                tempLimit = (tempLimit >= 50) ? 50 : tempLimit + 1;
                break;
            case 4:  // 新增湿度上限调整
                humiLimit = (humiLimit >= 100) ? 100 : humiLimit + 1;
                break;
        }
    }

    // 按键3：减少值
    if(Key_Scan(KEY_PORT, KEY3_PIN)) {
        switch(timeEditMode) {
            case 1:  // 小时
                currentTime.hours = (currentTime.hours == 0) ? 23 : currentTime.hours - 1;
                break;
            case 2:  // 分钟
                currentTime.minutes = (currentTime.minutes == 0) ? 59 : currentTime.minutes - 1;
                break;
            case 3:  // 温度上限
                tempLimit = (tempLimit == 0) ? 0 : tempLimit - 1;
                break;
            case 4:  // 新增湿度上限调整
                humiLimit = (humiLimit == 0) ? 0 : humiLimit - 1;
                break;
        }
    }

        // 显示更新
        Time_Display();
        Delay_ms(100);  // 主循环延时
    }
}
