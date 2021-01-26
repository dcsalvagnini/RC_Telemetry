#include "SoftwareSerial.h"
#include "TinyGPS.h"
#include <SparkFun_ADXL345.h>

SoftwareSerial gpsSerial(10,11);
TinyGPS gps;

long lat, lon;
int led = 9;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200);
  gpsSerial.begin(9600); // connect gps sensor

  pinMode(led, OUTPUT);

  header();
}

void loop() {
  // put your main code here, to run repeatedly:

  blink(led, 1000);
  
  
  Serial.println(gpsSerial.available());
  Serial.println(gpsSerial.read());
  Serial.println(gps.encode(gpsSerial.read()));
  
  gps.encode(gpsSerial.read());

  gps.get_position(&lat,&lon); // get latitude and longitude
  // display position
  
  Serial.print("Position: ");
  Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
  Serial.print("lon: ");Serial.println(lon); // print longitude
  
  while(gpsSerial.available() > 0){ // check for gps data

    digitalWrite(led, HIGH);

    if(gps.encode(gpsSerial.read())){ // encode gps data
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
