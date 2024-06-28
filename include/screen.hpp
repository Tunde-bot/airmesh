#include <Adafruit_ST7789.h>
#include <Arduino.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#ifndef SCREEN_H
#define SCREEN_H

namespace screen {

const uint8_t WIDTH = 240;
const uint8_t HEIGHT = 135;

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas{WIDTH, HEIGHT};

/**
 * @brief Initializes the ST7789 Display to a resolution of `WIDTH` and `HEIGHT`
 *
 */
void init() {
  display.init(HEIGHT, WIDTH); // Init ST7789 240x135
  display.setRotation(3);

  pinMode(TFT_BACKLITE, OUTPUT);

  canvas.setFont(&FreeSans9pt7b);
}
/**
 * @brief Transfers everything drawn to the canvas onto the display
 * @note THIS MUST BE CALLED FOR LITERALLY ANYTHING TO SHOW UP ON THE SCREEN
 */
void draw() {
  display.drawRGBBitmap(0, 0, canvas.getBuffer(), WIDTH, HEIGHT);
  digitalWrite(TFT_BACKLITE, HIGH);
}
/**
 * @brief Resets the canvas in preparation for another frame, this should be
 * called before drawing anything to the canvas
 */
void reset() {
  canvas.fillScreen(0);
  canvas.setCursor(0, 15);
}

/**
 * @brief Displays the current program status on the screen, as an alternative
 * to `Serial.print`
 * @note  Resets and displays the canvas
 */
void set_status(const char *status) {
  reset();
  canvas.setFont(&FreeSans9pt7b);
  canvas.setTextColor(0xffff);
  canvas.print(status);
  draw();
}

} // namespace screen

#endif