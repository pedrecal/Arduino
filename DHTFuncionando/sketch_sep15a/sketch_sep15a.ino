#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT22


DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(3500);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println("Falha!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidade: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\n");
}
