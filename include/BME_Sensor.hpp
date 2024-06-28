#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;

float Temp = 0;
float Pressure = 0;
float Humidity = 0;
float GasRes = 0;
float Altitude = 0;

/**
 * @brief Start the BME688 Sensor
 */

void StartBME() {
    if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        while (1);
    }
}

/**
 * @brief Return temperature as a value of float.
 * 
 * @return float 
 */

float ReturnTemp() {
    bme.setTemperatureOversampling(BME680_OS_8X);
    Temp = bme.temperature;
    
    return Temp;
}

/**
 * @brief Return pressure as a value of float.
 * 
 * @return float 
 */

float ReturnPres() {
    bme.setPressureOversampling(BME680_OS_4X);

    Pressure = bme.pressure / 100;

    return Pressure;
}

/**
 * @brief Return humidity as a value of float.
 * 
 * @return float 
 */

float ReturnHumid() {
    bme.setHumidityOversampling(BME680_OS_2X);

    Humidity = bme.humidity;
    
    return Humidity;
}

/**
 * @brief Return gas resisatnce as a value of float.
 * 
 * @return float 
 */

float ReturnGasRes() {
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    
    GasRes = bme.gas_resistance / 1000;

    return GasRes;
}

/**
 * @brief Return altitude as a value of float.
 * 
 * @return float 
 */

float ReturnAlt() {
    Altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    
    return Altitude;
}
void BMEloop() {
  Serial.print("Temperature = ");
  Serial.print(ReturnTemp());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(ReturnPres());
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(ReturnHumid());
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(ReturnGasRes());
  Serial.println(" KOhms");

  Altitude = ReturnAlt();
}