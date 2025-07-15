#pragma once
#include "esp_camera.h"

static camera_config_t camera_config = {
      .pin_pwdn       = -1,
      .pin_reset      = -1,
      .pin_xclk       = 10,
      .pin_sccb_sda   = 40,
      .pin_sccb_scl   = 39,
      .pin_d7         = 48,
      .pin_d6         = 11,
      .pin_d5         = 12,
      .pin_d4         = 14,
      .pin_d3         = 16,
      .pin_d2         = 18,
      .pin_d1         = 17,
      .pin_d0         = 15,
      .pin_vsync      = 38,
      .pin_href       = 47,
      .pin_pclk       = 13,

      .xclk_freq_hz   = 20000000, // The clock frequency of the image sensor
      .fb_location = CAMERA_FB_IN_PSRAM, // Set the frame buffer storage location
      .pixel_format   = PIXFORMAT_JPEG, // The pixel format of the image: PIXFORMAT_ + YUV422|GRAYSCALE|RGB565|JPEG
      .frame_size     = FRAMESIZE_UXGA, // The resolution size of the image: FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
      .jpeg_quality   = 10, // The quality of the JPEG image, ranging from 0 to 63.
      .fb_count       = 1, // The number of frame buffers to use.
      .grab_mode      = CAMERA_GRAB_WHEN_EMPTY //  The image capture mode.
};
