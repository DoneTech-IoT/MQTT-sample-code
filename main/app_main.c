#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_log.h"
#include "MQTT_Interface.h"

static const char *TAG = "main";

QueueHandle_t MQTTDataFromBrokerQueue;
SemaphoreHandle_t MQTTConnectedSemaphore;
SemaphoreHandle_t MQTTErrorOrDisconnectSemaphore;

PublishConfig_str PublishConfig;
SubscriptionConfig_str SubscriptionConfig;
MQTT_Configuration_str Interface;
void app_main(void)
{

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    SubscriptionConfig.Qos = 1;
    SubscriptionConfig.Retain = 0;
    strcpy(SubscriptionConfig.Topic, "test/azmon/bib");

    PublishConfig.Qos = 1;
    PublishConfig.Retain = 0;
    strcpy(PublishConfig.Topic, "test/azmon/bib");

    Interface.ClientID = 2225;
    Interface.PublishConfig = &PublishConfig;
    Interface.SubscriptionConfig = &SubscriptionConfig;

    Interface.ConnectedSemaphore = &MQTTConnectedSemaphore;
    Interface.DataFromBrokerQueue = &MQTTDataFromBrokerQueue;
    Interface.ErrorOrDisconnectSemaphore = &MQTTErrorOrDisconnectSemaphore;

    esp_err_t error;

    error = MQTT_Init(&Interface);
    if (error == ESP_OK)
    {
        ESP_LOGI(TAG, "MQTT Inited!");
    }
    else if (error == ESP_FAIL)
    {
        ESP_LOGE(TAG, "MQTT iit fail!");
    }

}
