#pragma once
#include "driver/gpio.h"

#define NUM_PINS 25

#define GPIO_LED 21
#define GPIO_PIR 1

#define GPIO_LED_PIN_SEL ((1ULL<<GPIO_LED))
#define GPIO_PIR_PIN_SEL ((1ULL<<GPIO_PIR))

#define ESP_INTR_FLAG_DEFAULT 0

typedef void (*gpio_handler_t)(gpio_num_t pin);

void init_gpio(void);

void gpio_register_handler(gpio_num_t pin, gpio_handler_t handler);
