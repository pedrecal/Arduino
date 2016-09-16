/* A demo sketch for the Modern Device Rev P Wind Sensor
* Requires a Wind Sensor Rev P from Modern Device
* http://moderndevice.com/product/wind-sensor-rev-p/
*
* The Rev P requires at least at least an 8 volt supply. The easiest way to power it
* if you are using an Arduino is to use a 9 volt or higher supply on the external power jack
* and power the sensor from Vin.
*
* Hardware hookup
* Sensor     Arduino Pin
* Ground     Ground
* +10-12V      Vin
* Out          A0
* TMP          A2
*
* Paul Badger 2014
* code in the public domain
*/
#include <LiquidCrystal.h> //Carrega a biblioteca LCD
//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Array simbolo grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};



//const int OutPin[4]  = {A0, A1, A2, A3};   // wind sensor analog pin  hooked up to Wind P sensor "OUT" pin
//const int TempPin[4] = {A4, A5, A6, A7};   // temp sesnsor analog pin hooked up to Wind P sensor "TMP" pin
#define rht A5

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2); //Inicializa LCD
    lcd.clear(); //Limpa o LCD
    //Cria o caractere customizado com o simbolo do grau
    lcd.createChar(0, grau);
}

void loop() {

    // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
    // this scalin doesn't have any temperature correction in it yet
    // Leo comenzando en A0 hasta A3 y los presento
    for (int i=0; i<4; i++){
        int windADunits = analogRead(rht);
        float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
        Serial.print(windMPH);
        Serial.print(" MPH\t");

        lcd.setCursor(0,0);
        lcd.print("Umid : ");
        lcd.print(" ");
        lcd.setCursor(7,0);
        lcd.print(windMPH,1);
        lcd.setCursor(12,0);

        //Mostra o simbolo do grau formado pelo array
        lcd.write((byte)0);

        // temp routine and print raw and temp C
        int tempRawAD = analogRead(rht); 
        // Serial.print("RT ");    // print raw A/D for debug
        // Serial.print(tempRawAD);
        // Serial.print("\t");
       
        // convert to volts then use formula from datatsheet
        // Vout = ( TempC * .0195 ) + .400
        // tempC = (Vout - V0c) / TC   see the MCP9701 datasheet for V0c and TC
       
        float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195;
        Serial.print(tempC);
        Serial.println(" C ");

        //Mostra o simbolo do grau quadrado
        //lcd.print((char)223);
         
        lcd.setCursor(0,1);
        lcd.print("Temp : ");
        lcd.print(" ");
        lcd.setCursor(7,1);
        lcd.print(tempC,1);
        lcd.setCursor(12,1);
        lcd.print("c°");
    }
   
   
    delay(750);
}
