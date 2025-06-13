#include "lcd_screens.h"

lv_obj_t *make_home_screen()
{
    lv_obj_t *home_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(home_screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(home_screen, LV_OPA_COVER, LV_PART_MAIN);
    return home_screen;
}