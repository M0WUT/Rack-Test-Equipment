#include "lvgl.h"
#include "lcd_settings.h"
#include "lcd_screens.h"
#include <TFT_eSPI.h>

static const uint32_t screenWidth = TFT_WIDTH;
static const uint32_t screenHeight = TFT_HEIGHT;
lv_color_t black = lv_color_make(0, 0, 0);
lv_color_t white = lv_color_make(255, 255, 255);

const unsigned int framebufferSizeBytes = screenWidth * screenHeight * (LV_COLOR_DEPTH / 8) / 10;

void *framebuffer[framebufferSizeBytes];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

void setup()
{
  Serial.begin(115200);
  // TFT eSPI initialisation
  tft.begin();
  tft.initDMA();

  // LVGL initialisation
  lv_init();
  lv_tick_set_cb((lv_tick_get_cb_t)millis);

  // Create display
  static lv_display_t *lvDisplay = lv_tft_espi_create(screenWidth, screenHeight, framebuffer, sizeof(framebuffer) / sizeof(byte));
  //  Display settings
  lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
  lv_display_set_rotation(lvDisplay, LV_DISP_ROTATION_270);

  // Create different screens
  lv_obj_t *home_screen = make_home_screen();

  // Load home screen
  lv_scr_load(home_screen);
}

void loop()
{
  lv_task_handler();
}
