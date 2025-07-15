#ifndef HTTP_H
#define HTTP_H

#include <inttypes.h>
#include <esp_http_server.h>

static const char* HTTP_TAG = "HTTP_SERVER";

typedef struct {
        httpd_req_t *req;
        size_t len;
} jpg_chunking_t;

static size_t jpg_encode_stream(void * arg, size_t index, const void* data, size_t len) {
    jpg_chunking_t *j = (jpg_chunking_t *)arg;
    if(!index){
        j->len = 0;
    }

    if(httpd_resp_send_chunk(j->req, (const char *)data, len) != ESP_OK) {
        return 0;
    }
    j->len += len;
    return len;
}

esp_err_t jpg_httpd_handler(httpd_req_t *req);

httpd_handle_t start_webserver(void);

#endif
