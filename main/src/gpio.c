#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "GPIO";

static QueueHandle_t gpio_event_queue = NULL;

static gpio_handler_t gpio_handlers[NUM_PINS] = {0};

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (gpio_num_t) arg;
    xQueueSendFromISR(gpio_event_queue, &gpio_num, NULL);
}

static void gpio_event_handler_task(void* arg)
{
    uint32_t gpio_num;
    for(;;) {
        if (xQueueReceive(gpio_event_queue, &gpio_num, portMAX_DELAY) == pdPASS) {
          if (gpio_num >= 0 && gpio_num < NUM_PINS && gpio_handlers[gpio_num]) {
              gpio_handlers[gpio_num](gpio_num);
          }
        }
    }
}

void init_gpio(void)
{
    gpio_config_t io_conf = {};

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    ESP_ERROR_CHECK(gpio_config(&io_conf));
    gpio_set_level(GPIO_LED, 1);

    gpio_event_queue = xQueueCreate(10, sizeof(gpio_num_t));

    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT));

    xTaskCreate(gpio_event_handler_task, "gpio_task", 4096, NULL, 10, NULL);
}

void gpio_register_handler(gpio_num_t pin, gpio_handler_t handler)
{
    // TODO: This code should only be in debug
    if (pin < 0 || pin >= NUM_PINS) {
        ESP_LOGE(TAG, "invalid pin number: %d", pin);
        return;
    }

    gpio_handlers[pin] = handler;

    ESP_ERROR_CHECK(gpio_isr_handler_add(pin, gpio_isr_handler, (void*)pin));
}
