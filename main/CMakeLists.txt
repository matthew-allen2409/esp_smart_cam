set(SOURCES
    "main.c"
    "include/camera.h"
    "include/http.h"
    "include/wifi.h"
    "include/gpio.h"
    "include/motion.h"
    "include/sleep.h"
    "src/http.c"
    "src/wifi.c"
    "src/gpio.c"
    "src/motion.c"
    "src/sleep.c"
)

idf_component_register(SRCS ${SOURCES}
                    PRIV_REQUIRES spi_flash
                    PRIV_REQUIRES esp32-camera
                    PRIV_REQUIRES esp_http_server
                    PRIV_REQUIRES nvs_flash
                    PRIV_REQUIRES esp_wifi
                    PRIV_REQUIRES esp_timer
                    INCLUDE_DIRS "")
