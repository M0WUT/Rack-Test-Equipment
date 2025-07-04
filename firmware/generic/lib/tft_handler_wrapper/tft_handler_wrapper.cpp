#include "tft_handler_wrapper.h"

/*
This file is entirely a nasty hack to allow member functions of the TFTHandler class
to be passed to LVGL which uses C-style callbacks that cannot be in another namespace.

It does this by converting the various callback functions into static functions that point
at the instance of the class.

N.B. really bad things will happen if these callbacks are used while tft is unitialised

*/

static TFTHandler *tft;

static void lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmdSize, const uint8_t *param, size_t paramSize)
{
    return tft->lcd_send_cmd(disp, cmd, cmdSize, param, paramSize);
}

static void lcd_send_colour(lv_display_t *disp, const uint8_t *cmd, size_t cmdSize, uint8_t *param, size_t paramSize)
{
    return tft->lcd_send_colour(disp, cmd, cmdSize, param, paramSize);
}

static void lcd_dma_callback(EventResponderRef eventResponder)
{
    return tft->dma_callback(eventResponder);
}

TFTHandler *create_tft_handler(SPIClass *pspi, int gpioDc, int gpioCs, int gpioReset, int horRes, int verRes)
{
    tft = new TFTHandler(pspi, gpioDc, gpioCs, gpioReset, horRes, verRes);
    tft->create_lvgl_screen(lcd_send_cmd, lcd_send_colour, lcd_dma_callback);
    return tft;
}