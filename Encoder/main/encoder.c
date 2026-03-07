#include "encoder.h"
#include "driver/pulse_cnt.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "ENCODER";

static pcnt_unit_handle_t pcnt_unit = NULL;
static int32_t last_count = 0;
static int64_t last_time = 0;

void encoder_init(void)
{
    pcnt_unit_config_t unit_config = {
        .high_limit = 32767,
        .low_limit = -32768,
    };

    pcnt_new_unit(&unit_config, &pcnt_unit);

    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ENCODER_GPIO_A,
        .level_gpio_num = ENCODER_GPIO_B,
    };

    pcnt_channel_handle_t chan_a = NULL;
    pcnt_new_channel(pcnt_unit, &chan_a_config, &chan_a);

    pcnt_channel_set_edge_action(
        chan_a,
        PCNT_CHANNEL_EDGE_ACTION_INCREASE,
        PCNT_CHANNEL_EDGE_ACTION_DECREASE);

    pcnt_channel_set_level_action(
        chan_a,
        PCNT_CHANNEL_LEVEL_ACTION_KEEP,
        PCNT_CHANNEL_LEVEL_ACTION_INVERSE);

    pcnt_unit_enable(pcnt_unit);
    pcnt_unit_clear_count(pcnt_unit);
    pcnt_unit_start(pcnt_unit);

    ESP_LOGI(TAG, "Encoder inicializado");
}

int32_t encoder_get_count(void)
{
    int count = 0;
    pcnt_unit_get_count(pcnt_unit, &count);
    return count;
}

float encoder_get_rpm(void)
{
    int32_t count = encoder_get_count();

    int64_t now = esp_timer_get_time();

    float dt = (now - last_time) / 1000000.0;

    int32_t delta = count - last_count;

    float rpm = (delta / (float)PULSOS_POR_REV) * (60.0 / dt);

    last_count = count;
    last_time = now;

    return rpm;
}