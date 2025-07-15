#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "gpio.h"
#include "camera.h"
#include "motion.h"
#include "wifi.h"
#include "include/http.h"
#include "nvs_flash.h"

static const char *TAG = "CAMERA";

void app_main(void)
{
    init_gpio();
    motion_init();

    esp_err_t err;
    for (int i = 0; i < 5; i++) {
        err = esp_camera_init(&camera_config);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Camera init failed retrying: 0x%x", err);
        } else {
            break;
        }
    }

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed: 0x%x", err);
        return;
    }

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init();

    if (start_webserver() == NULL) {
        ESP_LOGE(HTTP_TAG, "http server failed to start");
    } else {
        ESP_LOGI(HTTP_TAG, "http server started");
    }
}
