#ifndef COLOURS_H
#define COLOURS_H

#include <lvgl.h>

#define M0WUT_DEFAULT_BACKGROUND lv_color_hex(0x080808)
#define M0WUT_DEFAULT_FOREGROUND lv_color_hex(0xe1970c)

const lv_color_t M0WUT_CHANNEL_COLOURS[] = {
    M0WUT_DEFAULT_FOREGROUND,
    lv_palette_main(LV_PALETTE_LIGHT_GREEN),
    lv_palette_main(LV_PALETTE_LIGHT_BLUE),
    lv_palette_main(LV_PALETTE_PINK),
    lv_palette_main(LV_PALETTE_YELLOW),
    lv_palette_main(LV_PALETTE_PURPLE),
    lv_palette_main(LV_PALETTE_BROWN),
    lv_palette_main(LV_PALETTE_INDIGO),

};

const int M0WUT_NUM_COLOURS = sizeof(M0WUT_CHANNEL_COLOURS) / sizeof(M0WUT_CHANNEL_COLOURS[0]);

#endif