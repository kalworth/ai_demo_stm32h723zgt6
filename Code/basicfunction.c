//
// Created by AdministratorWang on 2023/7/12.
//
#include "basicfunction.h"
#include "stdio.h"

/**
  * @brief  求字符串长度
  * @param  None
  * @note   None
  * @retval None
  */
uint32_t char_len(const char* s)
{
    uint32_t length;
    for(length = 0;s[length] != '\0';length ++);
    return length;
}

/**
  * @brief  求uint8_t数组长度
  * @param  None
  * @note   None
  * @retval None
  */
uint32_t uint8_len(const uint8_t* s)
{
    uint32_t length;
    for(length = 0;s[length] != '\0';length++);
    return length;
}
