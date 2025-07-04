#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#include <Arduino.h>
#include <SPI.h>
#include "lvgl.h"

class TFTHandler
{
public:
    TFTHandler(SPIClass *pspi, int gpioDc, int gpioCs, int gpioReset, int horRes, int verRes);

    lv_display_t *get_lvgl_display();

    void set_spi_settings(SPISettings settings);
    void lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmdSize, const uint8_t *param, size_t paramSize);
    void lcd_send_colour(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t paramSize);
    void dma_callback(EventResponderRef eventResponder);
    void create_lvgl_screen(lv_st7789_send_cmd_cb_t send_cmd_func, lv_st7789_send_color_cb_t send_colour_func, EventResponderFunction dma_callback);

private:
    SPIClass *_pspi;
    int _gpioDc;
    int _gpioCs;
    int _gpioReset;
    int _horRes;
    int _verRes;
    int _framebufferSizeBytes;
    void *_buf0;
    void *_buf1;
    SPISettings _spiSettings = SPISettings(40000000, MSBFIRST, SPI_MODE0);
    lv_display_t *_disp = NULL;
    EventResponder _callbackHandler;

    void _init_io();
    void _init_lvgl();
    void _reset_tft();
};
#endif