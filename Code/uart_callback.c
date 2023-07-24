//
// Created by AdministratorWang on 2023/7/5.
//
#include "uart_callback.h"
#include "usart_printf.h"

uint8_t rx_data[DATA_MAX_BYTE];                 // 串口1 接收缓冲
uint8_t esp_data;                               // 单字节缓冲

/**
  * @brief  串口接收中断回调函数
  * @param  None
  * @note   None
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    /* USART1 接收中断 */
    if (huart->Instance == USART1)
    {
        HAL_GPIO_TogglePin(led_blue_GPIO_Port,led_blue_Pin);
        union usart_float pIn;
        for(uint8_t i = 0;i < DATA_MAX_BYTE;i ++)
        {
            pIn.data_uint8[i] = rx_data[(DATA_MAX_BYTE-1-i)];        // 由高位到低位
        }
        usart_ai_run(&(pIn.data_float));
    }
    /* USART2 接收中断 */
    if (huart->Instance == USART2)
    {
        usart1_printf(&esp_data);
    }
}