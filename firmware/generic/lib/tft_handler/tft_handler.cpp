#include "tft_handler.h"

TFTHandler::TFTHandler(SPIClass *pspi, int gpioDc, int gpioCs, int gpioReset, int horRes, int verRes)
{

    // Copy variables into class members
    _pspi = pspi;
    _gpioDc = gpioDc;
    _gpioCs = gpioCs;
    _gpioReset = gpioReset;
    _horRes = horRes;
    _verRes = verRes;

    _init_io();

    _pspi->begin();

    _init_lvgl();

    _reset_tft();
}

void TFTHandler::set_spi_settings(SPISettings settings)
{
    _spiSettings = settings;
}

lv_display_t *TFTHandler::get_lvgl_display()
{
    return _disp;
}

// DMA / SPI Stuff
void TFTHandler::lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmdSize, const uint8_t *param, size_t paramSize)
{
    // Commands are only sent on startup
    // so don't bother with DMA
    LV_UNUSED(disp);
    _pspi->beginTransaction(_spiSettings);
    digitalWriteFast(_gpioDc, 0);
    digitalWriteFast(_gpioCs, 0);
    for (size_t i = 0; i < cmdSize; i++)
    {
        _pspi->transfer(cmd[i]);
    }
    digitalWriteFast(_gpioDc, 1);
    for (size_t i = 0; i < paramSize; i++)
    {
        _pspi->transfer(param[i]);
    }

    digitalWriteFast(_gpioCs, 1);
    _pspi->endTransaction();
}

void TFTHandler::lcd_send_colour(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, uint8_t *param, size_t paramSize)
{
    LV_UNUSED(disp);
    _pspi->beginTransaction(_spiSettings);
    digitalWriteFast(_gpioDc, 0);
    digitalWriteFast(_gpioCs, 0);
    for (size_t i = 0; i < cmd_size; i++)
    {
        _pspi->transfer(cmd[i]);
    }
    digitalWriteFast(_gpioDc, 1);
    _pspi->transfer((void *)param, nullptr, paramSize, _callbackHandler);
}

void TFTHandler::_init_io()
{
    pinMode(_gpioReset, OUTPUT);
    digitalWriteFast(_gpioReset, HIGH);

    pinMode(_gpioDc, OUTPUT);
    digitalWriteFast(_gpioDc, HIGH);

    pinMode(_gpioCs, OUTPUT);
    digitalWriteFast(_gpioCs, HIGH);
}

void TFTHandler::dma_callback(EventResponderRef eventResponder)
{
    digitalWriteFast(_gpioCs, HIGH);
    _pspi->endTransaction();
    lv_display_flush_ready(_disp);
}

void TFTHandler::_init_lvgl()
{
    lv_init();
    lv_tick_set_cb((lv_tick_get_cb_t)millis);
}

void TFTHandler::_reset_tft()
{
    digitalWriteFast(_gpioReset, 0);
    delay(100);
    digitalWriteFast(_gpioReset, 1);
    delay(100);
}

void TFTHandler::create_lvgl_screen(lv_st7789_send_cmd_cb_t send_cmd_func, lv_st7789_send_color_cb_t send_colour_func, EventResponderFunction dma_callback)
{

    _callbackHandler.attachImmediate(dma_callback);

    _disp = lv_st7789_create(_horRes, _verRes, LV_LCD_FLAG_NONE, send_cmd_func, send_colour_func);
    lv_st7789_set_invert(_disp, true);
    lv_display_set_rotation(_disp, LV_DISPLAY_ROTATION_270);

    // Buffers
    _framebufferSizeBytes = _horRes * _verRes * (LV_COLOR_DEPTH / 8) / 10;
    _buf0 = malloc(_framebufferSizeBytes);
    if (_buf0 == NULL)
    {
        Serial.println("Failed to allocated buf 0");
    }

    _buf1 = malloc(_framebufferSizeBytes);
    if (_buf1 == NULL)
    {
        Serial.println("Failed to allocated buf 0");
    }

    lv_display_set_buffers(_disp, _buf0, _buf1, _framebufferSizeBytes, LV_DISPLAY_RENDER_MODE_PARTIAL);
}