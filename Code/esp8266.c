//
// Created by AdministratorWang on 2023/7/12.
//
#include "esp8266.h"
#include "usart_printf.h"

#define esp8266_send_cmd(x)  usart2_printf((uint8_t*)x)
/**
  * @brief  esp8266重启
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_reset(void)
{
    esp8266_send_cmd("AT+RST\r\n");
    HAL_Delay(200);     //保证重启
}
/**
  * @brief  esp8266设置模式
  * @param  mode 见esp3266.h文件
  * @note   None
  * @retval None
  */
void esp8266_set_mode(ESP_MODE mode)
{
    switch (mode) {
        case STA_MODE:
            esp8266_send_cmd("AT+CWMODE_DEF=1\r\n");
            break;
        case AP_MODE:
            esp8266_send_cmd("AT+CWMODE_DEF=2\r\n");
            break;
        case STA_AP_MODE:
            esp8266_send_cmd("AT+CWMODE_DEF=3\r\n");
            break;
    }

}
/**
  * @brief  esp8266查询附近热点
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_wifi_search(void)
{
    HAL_Delay(2000);
    esp8266_send_cmd("AT+CWLAP\r\n");
    HAL_Delay(2000);
}

/**
  * @brief  esp8266查询本机ip地址
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_get_ip(void)
{
    HAL_Delay(1000);
    esp8266_send_cmd("AT+CIFSR\r\n");
    HAL_Delay(1000);
}
/**
  * @brief  esp8266连接热点
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_wifi_connect(void)
{
    esp8266_send_cmd("AT+CWJAP_DEF=");
    esp8266_send_cmd("\"");
    esp8266_send_cmd(WIFI_NAME);
    esp8266_send_cmd("\"");
    esp8266_send_cmd(",");
    esp8266_send_cmd("\"");
    esp8266_send_cmd(WIFI_PASSWORD);
    esp8266_send_cmd("\"");
    esp8266_send_cmd("\r\n");
    HAL_Delay(5000);
}
/**
  * @brief  ESP8266建立tcp连接
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_tcp_connect(void)
{
    HAL_Delay(3000);
    esp8266_send_cmd("AT+CIPSTART=\"TCP\",");
    esp8266_send_cmd("\"");
    esp8266_send_cmd(TCP_IP);
    esp8266_send_cmd("\"");
    esp8266_send_cmd(",");
    esp8266_send_cmd(TCP_PORT);
    esp8266_send_cmd("\r\n");
    HAL_Delay(1000);
}
/**
  * @brief  esp8266查询网络连接状态
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_get_network_info(void)
{
    esp8266_send_cmd("AT+CIPSTATUS\r\n");
    HAL_Delay(1000);
}
/**
  * @brief  esp8266设置透传模式
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_set_trans(uint8_t mode)
{
    switch (mode) {
        case 0:
            esp8266_send_cmd("AT+CIPMODE=0\r\n");
            break;
        case 1:
            esp8266_send_cmd("AT+CIPMODE=1\r\n");
            break;
        default:
            esp8266_send_cmd("esp8266_set_trans_error!\r\n");
            break;
    }
    HAL_Delay(1000);
}
/**
  * @brief  设置esp8266连接模式
  * @param  mode 1-多连接模式(非透传) 0-单连接模式 （服务器只支持多链接)
  * @note   None
  * @retval None
  */
void esp8266_set_connect_mode(uint8_t mode)
{
    switch (mode) {
        case 0:
            esp8266_send_cmd("AT+CIPMUX=0\r\n");
            break;
        case 1:
            esp8266_send_cmd("AT+CIPMUX=1\r\n");
        default:
            esp8266_send_cmd("esp8266_set_connect_mode_error\r\n");
            break;
    }
}
  
/**
  * @brief  esp8266发送数据
  * @param  data 发送数据指针
  * @note   要在开启透传模式之后使用
  * @retval None
  */
void esp8266_tcp_send(uint8_t* data)
{
    esp8266_send_cmd("AT+CIPSEND\r\n");
    HAL_Delay(1000);
    esp8266_send_cmd(data);
}
/**
  * @brief  关闭tcp传输
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_tcp_closed(void)
{
    esp8266_send_cmd("AT+CIPCLOSE\r\n");
    HAL_Delay(200);
}

/**
  * @brief  esp8266 建立tcp服务器
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_set_tcp_sever(void)
{
    esp8266_send_cmd("AT+CIPSERVER=1\r\n");
    HAL_Delay(1000);
}

/**
  * @brief  esp8266恢复出厂设置
  * @param  None
  * @note   None
  * @retval None
  */
void esp8266_reset_source(void)
{
    esp8266_send_cmd("AT+RESTORE\r\n");
    HAL_Delay(1000);
}