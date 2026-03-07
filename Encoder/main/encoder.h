#ifndef ENCODER_H
#define ENCODER_H

#include "driver/pulse_cnt.h"
#include "esp_err.h"

#define ENCODER_GPIO_A 18
#define ENCODER_GPIO_B 19

#define PULSOS_POR_REV 1024

void encoder_init(void);
int32_t encoder_get_count(void);
float encoder_get_rpm(void);

#endif