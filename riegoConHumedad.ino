#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);//nuevo

int bomba = 8;
int  humedad;
int ledRojo = 13;
int ledAzul = 12;
int ledVerde = 11;

int estado = 0;
void setup()
{
  lcd.begin(0x3F,16,2);//nuevo
  Serial.begin(9600);
  pinMode(bomba,OUTPUT);  
  pinMode(A0, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  //lcd.print(humedad);
  //lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Bomba Encendida ");
  digitalWrite(ledVerde,HIGH);//Enciende el led verde
}

void loop()
{
   humedad = (100 - map(analogRead(A0),0,1023,0,100)); // Con esto conseguimos el porcentage de humedad en tantos por cien (el 1.45 puede variar segun el sensor de humedad).
  if(Serial.available()>0)
    {
    estado = Serial.read();
    }
    switch(estado){
      case 'B':
      digitalWrite(bomba, HIGH);
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      digitalWrite(ledVerde,LOW);//Apaga el led verde
        lcd.setCursor(0,0);
        lcd.print(" Bomba Apagada  ");
        //lcd.print(humedad);
        //lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("               ");
      break;
      case 'A':
      digitalWrite(bomba, LOW);
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      digitalWrite(ledVerde,HIGH);//Enciende el led verde
        lcd.setCursor(0,0);
        lcd.print(" Bomba Encendida ");
        //lcd.print(humedad);
        //lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("               ");
      break;
      case 'C':
            Serial.print(humedad);Serial.println (" %");
        if(humedad < 20){
             Serial.println("Tierra seca, encendiendo bomba automatica");
            digitalWrite(bomba, LOW);
            digitalWrite(ledRojo,HIGH);
            digitalWrite(ledAzul,LOW);
            digitalWrite(ledVerde,HIGH);//Apaga el led verde
            lcd.setCursor(0,0);
            lcd.print("Tierra Seca: ");
            lcd.print(humedad);
            lcd.print(" %");
              //delay(1000);
            lcd.setCursor(0,1);
            lcd.print("Regando...     ");
              //delay(1);
              //lcd.clear();
          }
        if(humedad > 20){
            
            Serial.println("Tierra humeda, apagando bomba automaticamente");
             digitalWrite(bomba, HIGH);
             digitalWrite(ledRojo,LOW);
            digitalWrite(ledAzul,HIGH);
            digitalWrite(ledVerde,LOW);//Apaga el led verde
            lcd.setCursor(0,0);
            lcd.print("  Tierra Humeda  ");
              //lcd.print(humedad);
              //lcd.print(" %");
              //delay(1000);
            lcd.setCursor(0,1);
              //lcd.print(humedad);
            lcd.print("  Bomba Apagada ");
              //delay(1);
          }
        delay(1000);
      break;
      case 'D':
      digitalWrite(bomba, HIGH);//Lo apaga y vuelve a leer el estado
      //estado = Serial.read();
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      digitalWrite(ledVerde,LOW);//Apaga el led verde
      lcd.setCursor(0,0);
      lcd.print("  Bomba Apagada ");
      lcd.setCursor(0,1);
      //lcd.print(humedad);
      lcd.print("                    ");
      break;
      }


  // Monitorizar los parametros.
  
  
  
  
}

