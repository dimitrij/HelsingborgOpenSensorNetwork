// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 5     // what pin we're connected to
#define SensorPin A0
 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

int SoundAverage = 0;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  SoundAverage = analogRead(SensorPin);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
   
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  
  Serial.print("HUMIDITY:"); 
  Serial.print(h);
  Serial.print("\t");
  Serial.print("TEMPERATURE:"); 
  Serial.print(t);
  Serial.print("\t");  
  SoundAverage = (SoundAverage + analogRead(SensorPin)) / 2;
  
  Serial.print("SOUNDLEVEL:");
  Serial.print(SoundAverage);
  Serial.println();

}
