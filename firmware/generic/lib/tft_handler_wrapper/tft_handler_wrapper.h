#ifndef TFT_HANDLER_WRAPPER_H
#define TFT_HANDLER_WRAPPER_H

#include "tft_handler.h"

TFTHandler *create_tft_handler(SPIClass *pspi, int gpioDc, int gpioCs, int gpioReset, int horRes, int verRes);

#endif