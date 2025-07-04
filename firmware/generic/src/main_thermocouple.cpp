#include "main.h"

static const uint32_t screenWidth = TFT_WIDTH;
static const uint32_t screenHeight = TFT_HEIGHT;

const unsigned int framebufferSizeBytes = screenWidth * screenHeight * (LV_COLOR_DEPTH / 8) / 10;
void *framebuffer[2][framebufferSizeBytes];

static lv_display_t *disp;

// DMA / SPI Stuff
SPISettings spiSettings = SPISettings(40000000, MSBFIRST, SPI_MODE0);
volatile bool dmaBusy = false;
EventResponder callbackHandler;

static void lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmdSize, const uint8_t *param, size_t paramSize)
{
  // Commands are only sent on startup
  // so don't bother with DMA
  LV_UNUSED(disp);
  SPI.beginTransaction(spiSettings);
  digitalWriteFast(TFT_DC, 0);
  digitalWriteFast(TFT_CS, 0);
  for (size_t i = 0; i < cmdSize; i++)
  {
    SPI.transfer(cmd[i]);
  }
  digitalWriteFast(TFT_DC, 1);
  for (size_t i = 0; i < paramSize; i++)
  {
    SPI.transfer(param[i]);
  }
  SPI.endTransaction();
  digitalWriteFast(TFT_CS, 1);
}

void dmaCallback(EventResponderRef eventResponder)
{
  SPI.endTransaction();
  digitalWriteFast(TFT_CS, HIGH);
  dmaBusy = false;
  lv_display_flush_ready(disp);
}

static void lcd_send_colour(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t param_size)
{
  LV_UNUSED(disp);
  SPI.beginTransaction(spiSettings);
  digitalWriteFast(TFT_DC, 0);
  digitalWriteFast(TFT_CS, 0);
  for (size_t i = 0; i < cmd_size; i++)
  {
    SPI.transfer(cmd[i]);
  }
  digitalWriteFast(TFT_DC, 1);
  SPI.transfer((void *)param, nullptr, param_size, callbackHandler);
}

void setup()
{
  pinMode(TFT_RST, OUTPUT);
  digitalWriteFast(TFT_RST, HIGH);

  pinMode(TFT_DC, OUTPUT);
  digitalWriteFast(TFT_DC, HIGH);

  pinMode(TFT_CS, OUTPUT);
  digitalWriteFast(TFT_CS, HIGH);

  Serial.begin(9600);
  SPI.begin();

  callbackHandler.attachImmediate(&dmaCallback);

  // LVGL initialisation
  lv_init();
  lv_tick_set_cb((lv_tick_get_cb_t)millis);

  // Reset LCD
  digitalWriteFast(TFT_RST, 0);
  delay(100);
  digitalWriteFast(TFT_RST, 1);
  delay(100);
  // Display setup
  disp = lv_st7789_create(TFT_WIDTH, TFT_HEIGHT, LV_LCD_FLAG_NONE, lcd_send_cmd, lcd_send_colour);
  lv_st7789_set_invert(disp, true);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

  // Buffers
  lv_display_set_buffers(disp, framebuffer[0], framebuffer[1], framebufferSizeBytes, LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_obj_t *main_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(main_scr, lv_color_black(), 0);
  lv_screen_load(main_scr);

  lv_obj_t *spinner = lv_spinner_create(main_scr);
  lv_obj_set_size(spinner, 240, 240);
  lv_obj_center(spinner);
  lv_spinner_set_anim_params(spinner, 1000, 200);
}

void loop()
{
  lv_task_handler();
}
