#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#include "esp_sleep.h"
#include "gpio.h"
#include "sleep.h"

#define TAG "SLEEP"

static void sleep_task(void* args)
{
    
}

void sleep_init()
{
    ESP_ERROR_CHECK(gpio_wakeup_enable(GPIO_PIR, GPIO_INTR_HIGH_LEVEL));
    ESP_ERROR_CHECK(esp_sleep_enable_gpio_wakeup());

    
}
