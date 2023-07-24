//
// Created by AdministratorWang on 2023/7/5.
//

#include "tim_callback.h"

/**
  * @brief  定时器中断回调函数
  * @param  htim   hal定时器
  * @note   None
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t tim6_ms = 0;    // TIM6时基 单位:ms
    /* TIM6(基本定时器) 1ms中断 */
    if(htim->Instance == TIM6)
    {
        tim6_ms ++;
    }
}