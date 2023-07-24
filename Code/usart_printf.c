//
// Created by AdministratorWang on 2023/7/5.
//
#include "usart.h"
#include "basicfunction.h"
/**
  * @brief  printf重定向(gcc)
  * @param  None
  * @note   None
  * @retval None
  */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
/**
  * @brief  串口1发送数据
  * @param  data    8位数组指针
  * @note   None
  * @retval None
  */
void usart1_printf(uint8_t* data)
{
    HAL_UART_Transmit(&huart1,data, uint8_len(data),HAL_MAX_DELAY);
}
/**
  * @brief  串口2发送数据
  * @param  data    8位数组指针
  * @note   None
  * @retval None
  */
void usart2_printf(uint8_t* data)
{
    HAL_UART_Transmit(&huart2,data, uint8_len(data),HAL_MAX_DELAY);
}

