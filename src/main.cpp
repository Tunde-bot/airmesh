#include "includes.hpp"

void setup() {
  screen::init();

  screen::set_status("Initializing Serial Monitor...");
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  screen::set_status("Initializing GPS...");
  gpsStart();

  screen::set_status("Initializing SGP & BME...");
  if (!sgp.begin()) {
    screen::set_status("SGP40 sensor not found :(");
    while (1)
      ;
  }

  if (!bme.begin()) {
    screen::set_status("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  screen::set_status("Finished setup");
}

void loop() {
  delay(1000);

  screen::reset();

  // put your main code here, to run repeatedly:
  sgpLoop();
  BMEloop();
  gpsLoop();
  screen::canvas.print("H/T/P: ");
  screen::canvas.print(ReturnHumid()), screen::canvas.print(", ");
  screen::canvas.print(ReturnTemp()), screen::canvas.print(", ");
  screen::canvas.println(ReturnPres());
  screen::canvas.print("VOC: ");
  screen::canvas.println(returnVoc());
  
  gpsPrint();
    
    // screen::canvas.setTextSize(1); screen::canvas.print("(last seen)"); screen::canvas.setTextSize(2); screen::canvas.print(": ");
    

  // screen::canvas.print("Time: ");
  // if (GPS.hour < 10)
  //   screen::canvas.print('0');
  // screen::canvas.print(GPS.hour, DEC), screen::canvas.print(':');

  // if (GPS.minute < 10)
  //   screen::canvas.print('0');
  // screen::canvas.print(GPS.minute, DEC), screen::canvas.print(':');

  // if (GPS.seconds < 10)
  //   screen::canvas.print('0');
  // screen::canvas.print(GPS.seconds, DEC), screen::canvas.print('.');

  // if (GPS.milliseconds < 10)
  //   screen::canvas.print("00");
  // else if (GPS.milliseconds > 9 && GPS.milliseconds < 100)
  //   screen::canvas.print("0");
  // screen::canvas.println(GPS.milliseconds);

  // screen::canvas.print("Date: ");
  // screen::canvas.print(GPS.day, DEC), screen::canvas.print('/');
  // screen::canvas.print(GPS.month, DEC), screen::canvas.print("/20");
  // screen::canvas.println(GPS.year, DEC);
  // screen::canvas.print("Fix: "), screen::canvas.print((int)GPS.fix);
  // screen::canvas.print(" quality: ");
  // screen::canvas.println((int)GPS.fixquality);
  // if (GPS.fix) {
  //   screen::canvas.print("Location: ");
  //   screen::canvas.print(GPS.latitude, 4), screen::canvas.print(GPS.lat);
  //   screen::canvas.print(", ");
  //   screen::canvas.print(GPS.longitude, 4), screen::canvas.println(GPS.lon);
  //   Serial.print("Speed (knots): "); Serial.println(GPS.speed);
  //   Serial.print("Angle: "); Serial.println(GPS.angle);
  //   Serial.print("Altitude: "); Serial.println(GPS.altitude);
  //   Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
  // }

  screen::draw();
}
