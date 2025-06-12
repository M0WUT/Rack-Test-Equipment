#include "lvgl.h"
#include "lcd_settings.h"
#include <TFT_eSPI.h>

static const uint32_t screenWidth = TFT_WIDTH;
static const uint32_t screenHeight = TFT_HEIGHT;
lv_color_t black = lv_color_make(0, 0, 0);
lv_color_t white = lv_color_make(255, 255, 255);

const unsigned int framebufferSize = screenWidth * screenHeight / 10;
uint16_t framebuffer[3][framebufferSize];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

void setup()
{
  // put your setup code here, to run once:
  tft.begin();
  tft.setRotation(1);
  tft.initDMA();
  // tft.startWrite();
  tft.fillScreen(TFT_GREENYELLOW);

  // lv_init();
  // static auto *lvDisplay = lv_display_create(screenWidth, screenHeight);
  // lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
  // lv_display_set_flush_cb(lvDisplay, my_disp_flush);
  // lv_display_set_buffers(lvDisplay, framebuffer[0], framebuffer[1], framebufferSize, LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
