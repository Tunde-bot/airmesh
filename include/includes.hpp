//libraries
#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "Adafruit_SGP40.h" //SGP Sensor
#include "Adafruit_SHT31.h" //SGP Sensor
#include "Adafruit_MQTT.h"
#include "ArduinoHttpClient.h"
#include <Adafruit_Sensor.h>   // FOR BME
#include <Wire.h> //FOR BME
#include <SPI.h>  // FOR BME
#include "Adafruit_BME680.h" //BME Sensor

//other files
#include <config.hpp>
#include <GPS_Sensor.hpp>
#include <SGP_Sensor.hpp>
#include <screen.hpp>