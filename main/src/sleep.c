#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"

#include "gpio.h"
#include "motion.h"
#include "sleep.h"

#define TAG "SLEEP"

static void sleep_timer_callback(void* args)
{
    ESP_LOGI(TAG, "TIME TO SLEEP");
    // ESP_ERROR_CHECK(gpio_wakeup_enable(GPIO_PIR, GPIO_INTR_HIGH_LEVEL));
}

static void motion_event_handler(void* args, esp_event_base_t base, int32_t id, void* event_data)
{
    if (base == MOTION_EVENTS && id == MOTION_DETECTED) {
        // stop timer
        ESP_LOGI(TAG, "stopping timer");
        ESP_ERROR_CHECK(esp_timer_stop(sleep_timer));
    } else if (base == MOTION_EVENTS && id == MOTION_ENDED) {
        // start timer
        ESP_LOGI(TAG, "starting timer");
        ESP_ERROR_CHECK(esp_timer_start_once(sleep_timer, SLEEP_TIMER_DELAY));
    }
}

void sleep_init()
{
    ESP_ERROR_CHECK(esp_sleep_enable_gpio_wakeup());

    ESP_ERROR_CHECK(esp_event_handler_register(MOTION_EVENTS, ESP_EVENT_ANY_ID, motion_event_handler, NULL));
    
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &sleep_timer));
    ESP_ERROR_CHECK(esp_timer_start_once(sleep_timer, SLEEP_TIMER_DELAY));
}
