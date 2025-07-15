#include "motion.h"
#include "gpio.h"
#include "driver/gpio.h"
#include "esp_log.h"

void handle_pir_gpio_event(gpio_num_t pin_number)
{
    int pin_level = gpio_get_level(pin_number);
    
    switch (pin_level) {
        case 0:
          ESP_LOGI("MOTION", "no motion");
          gpio_set_level(GPIO_LED, 1);
          break;
        case 1:
          ESP_LOGI("MOTION", "motion");
          gpio_set_level(GPIO_LED, 0);
          break;
    }
}

void motion_init(void)
{
        gpio_config_t io_conf = {};

        io_conf.intr_type = GPIO_INTR_ANYEDGE;
        io_conf.pin_bit_mask = GPIO_PIR_PIN_SEL;
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pull_up_en = 1;
        io_conf.pull_down_en = 0;
        ESP_ERROR_CHECK(gpio_config(&io_conf));

        gpio_register_handler(GPIO_PIR, handle_pir_gpio_event);
}
