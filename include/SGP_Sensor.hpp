#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"
#include "Arduino.h"
#include "BME_Sensor.hpp"
Adafruit_SGP40 sgp;

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

void sgpLoop() {
  int32_t voc_index;
  bme.setTemperatureOversampling(BME680_OS_8X);
  Temp = bme.temperature;
  bme.setHumidityOversampling(BME680_OS_2X);
  Humidity = bme.humidity;
  voc_index = sgp.measureVocIndex(Temp, Humidity);
  Serial.print("Voc Index: ");
  Serial.println(voc_index);
}

/*
return the air quality value
*/
float returnVoc(){
  bme.setTemperatureOversampling(BME680_OS_8X);
  Temp = bme.temperature;
  bme.setHumidityOversampling(BME680_OS_2X);
  Humidity = bme.humidity;
  return sgp.measureVocIndex(Temp, Humidity);
}
