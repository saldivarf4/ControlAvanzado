#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "encoder.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    encoder_init();

    while (1)
    {
        int32_t count = encoder_get_count();
        float rpm = encoder_get_rpm();

        ESP_LOGI(TAG, "Pulsos: %ld | RPM: %.2f", count, rpm);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}