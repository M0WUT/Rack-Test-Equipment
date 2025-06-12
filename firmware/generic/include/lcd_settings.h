
// LCD Properties
#define ST7789_DRIVER
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_RGB_ORDER TFT_BGR

// Pin definitions
#define TFT_SPI_PORT 0
#define RP2040_PIO_CLK_DIV 3

#define TFT_MISO 4
#define TFT_MOSI 3
#define TFT_SCLK 2
#define TFT_CS 5
#define TFT_DC 6
#define TFT_RST 7
#define TFT_BL 8
#define TFT_BACKLIGHT_ON HIGH

// Fonts
#define LOAD_GLCD 1
#define LOAD_FONT2 1
#define LOAD_FONT4 1
#define LOAD_FONT6 1
#define LOAD_FONT7 1
#define LOAD_FONT8 1
#define LOAD_GFXFF 1
#define SMOOTH_FONT 1

// SPI Configuration
#define SPI_FREQUENCY 27000000