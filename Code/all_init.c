//
// Created by AdministratorWang on 2023/7/5.
//
#include "all_init.h"
#include "main.h"
#include "dts.h"
#include "tim.h"
#include "usart.h"
#include "headfiles.h"

/**
  * @brief  额外增加的初始化
  * @param  None
  * @note   None
  * @retval None
  */
void all_init(void) {
    // 数字温度传感器 初始化
    HAL_DTS_Start(&hdts);
    // 基本定时器TIM6 开启
    HAL_TIM_Base_Start_IT(&htim6);
    // 神经网络模型 初始化
    ai_init();
    // 神经网络模型 验证
    ai_val();
    // 串口1&2 接收中断
    HAL_UART_Receive_IT(&huart1,rx_data,DATA_MAX_BYTE);
    HAL_UART_Receive_IT(&huart2, &esp_data, 1);
    // esp8266 重启
    // esp8266_reset_source();
    //esp8266_reset();
    // esp8266设置STA模式
    //esp8266_set_mode(STA_AP_MODE);
    HAL_Delay(1000);
}