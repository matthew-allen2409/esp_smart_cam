#pragma once
#include "driver/gpio.h"

void motion_init(void);

void handle_pir_gpio_event(gpio_num_t pin_number);
