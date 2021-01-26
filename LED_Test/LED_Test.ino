#include <SPI.h>
#include <SD.h>
#include "SoftwareSerial.h"
#include "TinyGPS.h"
#include <SparkFun_ADXL345.h>

//SoftwareSerial gpsSerial(19, 18);
TinyGPS gps;

long lat, lon;
int led = 9;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200);
  Serial1.begin(9600); // connect gps sensor

  pinMode(led, OUTPUT);

  header();
}

void loop() {
  // put your main code here, to run repeatedly:

  blink(led, 1000);
  
  
  Serial.println(Serial1.available());
  Serial.println(Serial1.read());
  Serial.println(gps.encode(Serial1.read()));
  
  gps.encode(Serial1.read());

  gps.get_position(&lat,&lon); // get latitude and longitude
  // display position
  
  Serial.print("Position: ");
  Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
  Serial.print("lon: ");Serial.println(lon); // print longitude
  
  while(Serial1.available() > 0){ // check for gps data

    digitalWrite(led, HIGH);

    if(gps.encode(Serial1.read())){ // encode gps data
      gps.get_position(&lat,&lon); // get latitude and longitude
      // display position
      
      Serial.print("Position: ");
      Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
      Serial.print("lon: ");Serial.println(lon); // print longitude
    }
  }
  
}

void blink (int l, int t) {
  digitalWrite(l, HIGH);

  delay(t);

  digitalWrite(l, LOW);

  delay(t);
}

void header () {
  Serial.print("TinyGPS Version: " );
  Serial.println(TinyGPS::library_version());
}
