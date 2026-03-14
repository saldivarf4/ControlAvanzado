#include "encoder.h"
#include "driver/pcnt.h"

#define ENCODER_A_GPIO 4
#define ENCODER_B_GPIO 5

#define PCNT_UNIT_USED PCNT_UNIT_0

#define PCNT_HIGH_LIMIT 32767
#define PCNT_LOW_LIMIT  -32768

void encoder_init()
{
    pcnt_config_t pcnt_config_A = {
        .pulse_gpio_num = ENCODER_A_GPIO,
        .ctrl_gpio_num = ENCODER_B_GPIO,
        .channel = PCNT_CHANNEL_0,
        .unit = PCNT_UNIT_USED,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_DEC,
        .lctrl_mode = PCNT_MODE_REVERSE,
        .hctrl_mode = PCNT_MODE_KEEP,
        .counter_h_lim = PCNT_HIGH_LIMIT,
        .counter_l_lim = PCNT_LOW_LIMIT
    };

    pcnt_config_t pcnt_config_B = {
        .pulse_gpio_num = ENCODER_B_GPIO,
        .ctrl_gpio_num = ENCODER_A_GPIO,
        .channel = PCNT_CHANNEL_1,
        .unit = PCNT_UNIT_USED,
        .pos_mode = PCNT_COUNT_DEC,
        .neg_mode = PCNT_COUNT_INC,
        .lctrl_mode = PCNT_MODE_REVERSE,
        .hctrl_mode = PCNT_MODE_KEEP,
        .counter_h_lim = PCNT_HIGH_LIMIT,
        .counter_l_lim = PCNT_LOW_LIMIT
    };

    pcnt_unit_config(&pcnt_config_A);
    pcnt_unit_config(&pcnt_config_B);

    pcnt_set_filter_value(PCNT_UNIT_USED, 100);
    pcnt_filter_enable(PCNT_UNIT_USED);

    pcnt_counter_pause(PCNT_UNIT_USED);
    pcnt_counter_clear(PCNT_UNIT_USED);
    pcnt_counter_resume(PCNT_UNIT_USED);
}

int16_t encoder_get_count()
{
    int16_t count = 0;
    pcnt_get_counter_value(PCNT_UNIT_USED, &count);
    return count;
}

void encoder_clear()
{
    pcnt_counter_clear(PCNT_UNIT_USED);
}