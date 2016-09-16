#include "DHT.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 6
#define DHTTYPE DHT22
//LDR
const int LDR = 0;
const int Led = 10;
int ValorLDR = 0;
int pwm = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(Led, OUTPUT);
}

void loop() {
  delay(3000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //LDR
  ValorLDR = analogRead(LDR);
  if(ValorLDR < 80)
  {
    analogWrite(Led, pwm);
    pwm++;
    delay(100);
  }
  else
  {
    digitalWrite(Led, LOW);
    pwm  = 0;
  }
  if(pwm > 255)
    pwm=255;
   //Fim LDR

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
  Serial.print(ValorLDR);
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Humidade:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp.:");
  lcd.print(t);
  lcd.print("C");
}

