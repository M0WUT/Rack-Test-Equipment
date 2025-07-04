#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#include <Arduino.h>
#include <SPI.h>
#include "lvgl.h"
#include "pinout.h"

lv_display_t *initialise_display(uint32_t hor_res, uint32_t ver_res);
#endif