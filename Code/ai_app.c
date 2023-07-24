//
// Created by AdministratorWang on 2023/7/6.
//
#include "ai_app.h"
#include "ai_platform.h"
#include "network.h"
#include "network_data.h"
#include "stdio.h"


/* ai相关本地变量 */
static ai_handle network;                                           // 网络模型
static float aiInData[AI_NETWORK_IN_1_SIZE];                        // 输入缓存
static float aiOutData[AI_NETWORK_OUT_1_SIZE];                      // 输出缓存
static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];         // 本地数组 激活
static ai_buffer *ai_input;                                         // 输入指针
static ai_buffer *ai_output;                                        // 输出指针

/* 验证集 */
#define val_len 10
static float val_data[val_len][AI_NETWORK_IN_1_SIZE] = {
        {(float)0.5},
        {(float)5.43},
        {(float)21.85},
        {(float)2.50},
        {(float)17.57},
        {(float)19.89},
        {(float)24.41},
        {(float)21.05},
        {(float)4.08},
        {(float)5.73}
};
static uint8_t val_label[val_len] = {
        0, 2, 3, 1, 3, 3, 3, 3, 1, 2
};

/**
  * @brief  模型初始化
  * @param  None
  * @note   None
  * @retval None
  */
void ai_init(void) {
    ai_error err;
    /* 创建一个包含激活缓冲区地址的本地数组 */
    const ai_handle act_addr[] = {activations};
    /* 创建模型示例 */
    err = ai_network_create_and_init(&network, act_addr, NULL);
    if (err.type != AI_ERROR_NONE) {

        printf("ai_network_create error - type=%d code=%d\r\n", err.type, err.code);
        Error_Handler();
    }

    ai_input = ai_network_inputs_get(network, NULL);
    ai_output = ai_network_outputs_get(network, NULL);
}

/**
  * @brief  模型运行
  * @param  pIn     输入指针
  * @param  pOut    输出指针
  * @note   None
  * @retval None
  */

void ai_run(float *pIn, float *pOut) {
    ai_i32 batch;
    ai_error err;

    /* 更新输入输出数据 */
    ai_input[0].data = AI_HANDLE_PTR(pIn);
    ai_output[0].data = AI_HANDLE_PTR(pOut);

    batch = ai_network_run(network, ai_input, ai_output);
    if (batch != 1) {
        err = ai_network_get_error(network);
        printf("AI ai_network_run error - type=%d code=%d\r\n", err.type, err.code);
        Error_Handler();
    }
}

/**
  * @brief  求取一维数组最大值索引
  * @param  values      数组首地址
  * @param  len         数组长度
  * @note   None
  * @retval None
  */
uint32_t argmax(const float *values, uint32_t len) {
    float max_value = values[0];
    uint32_t max_index = 0;

    for (uint32_t i = 1; i < len; i++) {
        if (values[i] > max_value) {
            max_value = values[i];
            max_index = i;
        }
    }

    return max_index;
}

/**
  * @brief  模型验证
  * @note   None
  * @retval None
  */
void ai_val(void) {
    uint8_t correct = 0;    // 正确率
    uint32_t predicted;        // 预测值

    printf("=======================================================\r\n");
    printf("Val  Start                                Size:      %d\r\n", val_len);

    for (uint32_t j = 0; j < val_len; j++) {

        for (uint32_t k = 0; k < AI_NETWORK_IN_1_SIZE; k++) {
            aiInData[k] = val_data[j][k];
        }

        ai_run(aiInData, aiOutData);

        for (uint32_t i = 0; i < AI_NETWORK_OUT_1_SIZE; i++) {
            printf("%8.6f ", aiOutData[i]);
        }

        predicted = argmax(aiOutData, AI_NETWORK_OUT_1_SIZE);
        printf("label:%d,predicted:%d\r\n", (int) val_label[j], (int) predicted);

        if (predicted == (uint32_t) val_label[j]) {
            correct++;
        }
    }

    printf("Val  End                                  Accuracy:%d%%\r\n", correct * 100 / val_len);
    printf("=======================================================\r\n");
}

/**
  * @brief  串口接收数据推理
  * @param  input 输入数据地址
  * @note   input 为一维数组
  * @retval None
  */
void usart_ai_run(float *input)
{
    uint32_t  i;        // 循环变量

    for(i =0;i < AI_NETWORK_IN_1_SIZE;i ++)
    {
        aiInData[i] = input[i];
    }

    ai_run(aiInData,aiOutData);

    uint32_t predicted;
    predicted = argmax(aiOutData, AI_NETWORK_OUT_1_SIZE);

    printf("input data : [");
    for(i = 0;i < AI_NETWORK_IN_1_SIZE;i ++)
    {
        (i == (AI_NETWORK_IN_1_SIZE - 1))?printf("%.2f]",input[i]):printf("%.2f ",input[i]);
    }
    printf("    predicted : [%d]\r\n",(int)predicted);
}