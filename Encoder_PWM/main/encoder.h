#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

void encoder_init(void);
int16_t encoder_get_count(void);
void encoder_clear(void);

#endif