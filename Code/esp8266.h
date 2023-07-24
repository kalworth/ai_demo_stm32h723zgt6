//
// Created by AdministratorWang on 2023/7/12.
//
#ifndef AI_DEMO_ESP8266_H
#define AI_DEMO_ESP8266_H
#include "main.h"

#define WIFI_NAME       "Tenda_448118"
#define WIFI_PASSWORD   ""
#define TCP_IP          "192.168.1.10"
#define TCP_PORT        "80"

/*  esp8266 模式 */
typedef enum {
    STA_MODE    =  1,
    AP_MODE     =  2,
    STA_AP_MODE =  3
}ESP_MODE;

void esp8266_reset(void);
void esp8266_set_mode(ESP_MODE mode);
void esp8266_wifi_search(void);
void esp8266_get_ip(void);
void esp8266_wifi_connect(void);
void esp8266_tcp_connect(void);
void esp8266_get_network_info(void);
void esp8266_set_trans(uint8_t mode);
void esp8266_set_connect_mode(uint8_t mode);
void esp8266_tcp_send(uint8_t* data);
void esp8266_tcp_closed(void);
void esp8266_set_tcp_sever(void);
void esp8266_reset_source(void);
#endif //AI_DEMO_ESP8266_H