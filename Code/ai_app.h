//
// Created by AdministratorWang on 2023/7/6.
//
#ifndef AI_DEMO_AI_APP_H
#define AI_DEMO_AI_APP_H
#include "main.h"

#define DATA_MAX_BYTE   (4)         // 4字节 对应 float

union usart_float
{
    uint8_t data_uint8[DATA_MAX_BYTE];
    float data_float;
};

void ai_init(void);
void ai_run(float *pIn, float *pOut);
uint32_t argmax(const float *values, uint32_t len);
void ai_val(void);
void usart_ai_run(float *input);
#endif //AI_DEMO_AI_APP_H
