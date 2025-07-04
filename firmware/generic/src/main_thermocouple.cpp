#include "main.h"

lv_display_t *disp;
TFTHandler *tft;

void setup()
{
  Serial.begin(9600);
  tft = create_tft_handler(&SPI, TFT_DC, TFT_CS, TFT_RST, TFT_WIDTH, TFT_HEIGHT);
  disp = tft->get_lvgl_display();

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
