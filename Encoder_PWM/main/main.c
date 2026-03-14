#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "encoder.h"
#include "motor.h"

static const char *TAG = "MAIN";

void app_main()
{
    encoder_init();
    motor_init();

    ESP_LOGI(TAG, "Sistema iniciado");

    // velocidad inicial
    motor_set_speed(400);

    while (1)
    {
        int16_t pulsos = encoder_get_count();

        ESP_LOGI(TAG, "Pulsos encoder: %d", pulsos);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}