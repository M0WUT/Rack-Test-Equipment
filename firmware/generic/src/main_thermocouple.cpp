#include "main.h"

lv_display_t *disp;
TFTHandler *tft;
lv_style_t *largeTextStyle;

static lv_obj_t *channelViewCells[MAX_GRID_CELLS];
GridHandler *gh;
int GRID_SIZE = 8;
const int READING_INTERVAL_MS = 1000;
int previous_reading_time_ms = 0;
int x = 1;
lv_obj_t *main_scr;

void setup()
{
  Serial.begin(9600);
  tft = create_tft_handler(&SPI, TFT_DC, TFT_CS, TFT_RST, TFT_WIDTH, TFT_HEIGHT);
  disp = tft->get_lvgl_display();

  main_scr = create_home_screen();
  lv_screen_load(main_scr);

  gh = new GridHandler(main_scr, channelViewCells, GRID_SIZE);

  for (int i = 0; i < GRID_SIZE; i++)
  {

    lv_obj_t *label = lv_label_create(main_scr);
    lv_label_set_text_fmt(label, "%d", i);
    lv_obj_set_style_text_color(label, M0WUT_CHANNEL_COLOURS[i % M0WUT_NUM_COLOURS], LV_PART_MAIN);
    const lv_font_t *font = gh->get_max_size_font();
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_center(label);
    gh->set_cell_contents(i, label);
  }

  Serial.println("Starting loop");
}

void loop()
{
  lv_task_handler();
  if (millis() - previous_reading_time_ms > READING_INTERVAL_MS)
  {
    gh->update_num_cells(x);
    for (int i = 0; i < x; i++)
    {

      lv_obj_t *label = lv_label_create(main_scr);
      lv_label_set_text_fmt(label, "%d", i);
      lv_obj_set_style_text_color(label, M0WUT_CHANNEL_COLOURS[i % M0WUT_NUM_COLOURS], LV_PART_MAIN);
      const lv_font_t *font = gh->get_max_size_font();
      lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
      lv_obj_center(label);
      gh->set_cell_contents(i, label);
    }

    previous_reading_time_ms = millis();
    if (x == 8)
    {
      x = 1;
    }
    else
    {
      x++;
    }
  }
}
