TA//Codi del sensor de temperatura i la pantalla icd i2c
//codi realitzat per: Pol R., Alfonso G. i Biel P.

#include <dht.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SFE_BMP180.h>
dht DHT;
SFE_BMP180 bmp180;
#define DHT11_PIN 5
int rainPin = A1;
int greenLED = 9;
int redLED = 10;
int blueLED = 11;
int thresholdValue = 500;
int ldr = A0;
int chk ;
int r;


byte dir = 0x3F  ;   //en algunes pantalles l'adreça del i2c pot ser diferent, per això, millor executar el programa d'escaeig avants de programar la direcció del dispositiu
LiquidCrystal_I2C
lcd( dir, 2, 1, 0, 4, 5, 6, 7);
int pantalla = 0;


#define I2C_ADDR    0x27 //cambiar si es necessari

void setup()
{
  lcd.begin (16, 2);   // Inicializar el display con 16 caraceres 2 lineas
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  bmp180.begin();
  // Serial.println(DHT_LIB_VERSION);
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode (blueLED, OUTPUT);

}
35*5+29*5+20*6
void loop()
{
  presion();
  anima();
  lluvia();
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(rainPin, LOW);
  delay(50);
  int luz = analogRead (ldr);

  if (luz < 50) {
    r = random(1, 2);
    if (r == 1) {
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
    }
    if (r == 2) {
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    }
    delay(1500);
  }
  else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  chk = DHT.read11(DHT11_PIN);
  switch (chk) {
    case DHTLIB_OK:
      // Serial.print("OK,\t");
      break;
  }

  if (pantalla == 0) {
    lcd.clear ();
    lcd.setCursor (1, 0);
    lcd.print (DHT.humidity, 1);
    lcd.setCursor (5, 0);
    lcd.print("% d'humitat");
    lcd.setCursor (1, 1);
    lcd.print(DHT.temperature, 1);
    lcd.setCursor (5, 1);
    lcd.print ("' celsius");
  }
  if (pantalla == 1) {
    lcd.clear ();
    lcd.setCursor (0, 0);
    lcd.print (DHT.humidity, 1);

    lcd.setCursor (4, 0);
    lcd.print("% d'humitat");
    lcd.setCursor (0, 1);
    lcd.print(DHT.temperature, 1);
    lcd.setCursor (4, 1);
    lcd.print ("' celsius");
    lcd.print (" |L");
  }
  if (Serial.available() > 0)
  {
    Serial.println ("start");
  }
  Serial.println (luz);
  Serial.println (DHT.humidity);
  Serial.println (DHT.temperature);
  Serial.println ("end");
delay(5000);
}



void anima()
{
  for (int i = 0; i > 2; i++) {
    for (int a = 0; a > 17; a++) {
      lcd.setCursor (a, i);
      lcd.print("-");
      delay (50);
    }
  }
}
void lluvia() {
  int sensorValue = analogRead(rainPin);
  if (sensorValue < thresholdValue ) {
    digitalWrite(redLED, HIGH);
    pantalla = 1;
  }
  else {
    digitalWrite (redLED, LOW);
    pantalla = 0;
  }
  delay(500);
}
void presion() {
  char status;
  double T,P;
 
  status = bmp180.startTemperature(); //Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {        
        delay(status); //Pausa para que finalice la lectura        
        status = bmp180.getPressure(P,T); //Obtenemos la presión
        if (status != 0)
        {                  
          Serial.print("Temperatura: ");
          Serial.print(T,2);
          Serial.print(" *C , ");
          Serial.print("Presion: ");
          Serial.print(P,2);
          Serial.println(" mb");          
        }      
      }      
    }   
  } 
  delay(1000);
}
//
// END OF FILE
//