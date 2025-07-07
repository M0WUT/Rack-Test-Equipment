#include "main_thermocouple.h"

lv_display_t *disp;
TFTHandler *tft;

void create_max_size_grid(lv_obj_t *obj, int numCells)
{
  lv_obj_update_layout(obj);
  lv_coord_t width = lv_obj_get_width(obj);
  lv_coord_t height = lv_obj_get_height(obj);

  Serial.println(width);
  Serial.println(height);

  int numRows, numCols;

  switch (numCells)
  {
  case 1:
    numRows = 1;
    numCols = 1;
    break;
  case 2:
    numRows = 2;
    numCols = 1;
    break;
  case 3: // Deliberate fallthrough
  case 4:
    numRows = 2;
    numCols = 2;
    break;
  case 5: // Deliberate fallthrough
  case 6:
    numRows = 2;
    numCols = 3;
    break;
  case 7: // Deliberate fallthrough
  case 8:
    numRows = 2;
    numCols = 4;
    break;
  case 9:
    numRows = 3;
    numCols = 3;
    break;
  default:
    // This assumes you'll never want more than 16 items
    // If you do, feel free to extend this table
    numRows = 4;
    numCols = 4;
    break;
  };

  int32_t rowDsc[numCols + 1];
  int32_t colDsc[numCols + 1];

  int rowHeight = height / numRows;
  int colWidth = width / numCols;

  for (int i = 0; i < numRows; i++)
  {
    rowDsc[i] = rowHeight;
  }
  rowDsc[numRows] = LV_GRID_TEMPLATE_LAST;

  for (int i = 0; i < numCols; i++)
  {
    colDsc[i] = colWidth;
  }
  colDsc[numCols] = LV_GRID_TEMPLATE_LAST;
  lv_obj_set_grid_dsc_array(obj, colDsc, rowDsc);
  lv_obj_update_layout(obj);
}

void setup()
{
  Serial.begin(9600);
  tft = create_tft_handler(&SPI, TFT_DC, TFT_CS, TFT_RST, TFT_WIDTH, TFT_HEIGHT);
  disp = tft->get_lvgl_display();

  lv_obj_t *main_scr = create_home_screen();
  lv_screen_load(main_scr);
  create_max_size_grid(main_scr, 8);
}

void loop()
{
  lv_task_handler();
}
