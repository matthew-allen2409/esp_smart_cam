#include <stdlib.h>
#include <inttypes.h>
#include <stddef.h>

#include "http.h"
#include "esp_err.h"
#include <esp_http_server.h>
#include "esp_log.h"
#include "esp_camera.h"

esp_err_t jpg_httpd_handler(httpd_req_t *req) {
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    size_t fb_len = 0;

    fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(HTTP_TAG, "Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    res = httpd_resp_set_type(req, "image/jpeg");
    if(res == ESP_OK){
        res = httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
    }

    if(res == ESP_OK) {
        if(fb->format == PIXFORMAT_JPEG) {
            fb_len = fb->len;
            res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
        } else {
            jpg_chunking_t jchunk = {req, 0};
            res = frame2jpg_cb(fb, 80, jpg_encode_stream, &jchunk)?ESP_OK:ESP_FAIL;
            httpd_resp_send_chunk(req, NULL, 0);
            fb_len = jchunk.len;
        }
    }
    esp_camera_fb_return(fb);
    // ESP_LOGI(TAG, "JPG: %uKB", (uint32_t)(fb_len/1024));
    return res;
}


httpd_uri_t uri_get = {
    .uri      = "/jpeg",
    .method   = HTTP_GET,
    .handler  = jpg_httpd_handler,
    .user_ctx = NULL
};

httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
    }

    /* If server failed to start, handle will be NULL */
    return server;
}
