#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor
#include <screen.hpp>
Adafruit_GPS GPS(&Wire);
#define GPSECHO false

// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 5000



void gpsStart(){
  GPS.begin(0x10); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  GPS.println(PMTK_Q_RELEASE);
  
}

void gpsLoop(){
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data 
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
}

//location->save(value, GPS.latitude, GPS.longitude, GPS.altitude);

/*
*/
void gpsPrint(){
  screen::canvas.print("Time: "); 
      if (GPS.hour < 10) { screen::canvas.print('0'); }
    screen::canvas.print(GPS.hour, DEC); screen::canvas.print(':');
    if (GPS.minute < 10) { screen::canvas.print('0'); }
    screen::canvas.print(GPS.minute, DEC);

    screen::canvas.print(" Date: ");
    screen::canvas.print(GPS.day, DEC); screen::canvas.print('/');
    screen::canvas.print(GPS.month, DEC); screen::canvas.print("/20");
    screen::canvas.println(GPS.year, DEC);
    screen::canvas.print("Fix: "); screen::canvas.print((int)GPS.fix);
    screen::canvas.print(" quality: "); screen::canvas.println((int)GPS.fixquality);
    
    screen::canvas.print("Long: "); 
    screen::canvas.println(GPS.longitude);
    screen::canvas.print("Lat: ");
    screen::canvas.println(GPS.latitude);
    screen::canvas.print("Altitude: "); screen::canvas.println(GPS.altitude);
}