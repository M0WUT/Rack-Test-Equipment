#include "lcd_screens.h"

lv_obj_t *create_home_screen()
{
    lv_obj_t *home_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(home_screen, M0WUT_DEFAULT_BACKGROUND, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(home_screen, LV_OPA_COVER, LV_PART_MAIN);
    return home_screen;
}