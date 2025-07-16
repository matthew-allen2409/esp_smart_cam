#pragma once
#include "driver/gpio.h"
#include "esp_event.h"

ESP_EVENT_DECLARE_BASE(MOTION_EVENTS);

typedef enum {
    MOTION_DETECTED,
    MOTION_ENDED
} motion_event_id_t;

void motion_init(void);

void handle_pir_gpio_event(gpio_num_t pin_number);
