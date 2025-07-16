#pragma once
#include "esp_timer.h"

#define SLEEP_TIMER_DELAY 30 * 1000 * 1000

void sleep_init(void);
static void sleep_timer_callback(void* args);

static const esp_timer_create_args_t timer_args = {
        .callback = sleep_timer_callback,
        .name = "sleep_timer_callback"
};
static esp_timer_handle_t sleep_timer;
