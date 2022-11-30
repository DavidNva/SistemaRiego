#include <LiquidCrystal.h>//Libreria para LCD
LiquidCrystal lcd(2,3,4,5,6,7);//pines a utilizar en arduino 

int bomba = 8;//Pin para conectar la bomba
int  humedad;//Variable para saber la humedad del suelo
int ledRojo = 13;//El led rojo indica que la tierra esta seca (debe encenderse la bomba)
int ledAzul = 12;//El led azul indica que la tierra esta humeda (debe apagarse la bomba)
int ledVerde = 11;//El led verde indica que la bomba esta encendida

int estado = 0;//Variable para conocer un estado inicial al inicar el programa
void setup()
{
  lcd.begin(0x3F,16,2);//
  Serial.begin(9600);
  //Las variables de entrada y salida 
  pinMode(bomba,OUTPUT); //Para la conexion con el modulo Relé
  pinMode(A0, INPUT);//Para el sensor de humedad
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  lcd.setCursor(0,0);//Al conectar el sistema a corriente, lo primero a mostrar será: 
  lcd.print("Iniciando...");//Indica que se inicia el sistema
  //lcd.print(humedad);
  //lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Bomba Encendida ");//Al encender la bomba se activa, por lo que:
  digitalWrite(ledVerde,HIGH);//Enciende el led verde
}

void loop()
{
   humedad = (100 - map(analogRead(A0),0,1023,0,100)); // Con esto conseguimos el porcentage de
                //humedad en tantos por cien (el 1.45 puede variar segun el sensor de humedad).
  if(Serial.available()>0)//En este caso se relaciona con la aplicacion creada en App inventor
    {
    estado = Serial.read();//Lee lo que se este arrojando 
    }
    switch(estado){//Al pulsar un boton de la aplicacion, ocurre un caso diferente, de los cuales:
      case 'B'://Significa que se pulso el boton de OFF (Apagar bomba).
      digitalWrite(bomba, HIGH);
      digitalWrite(ledRojo,LOW);//Apaga todos los leds
      digitalWrite(ledAzul,LOW);//
      digitalWrite(ledVerde,LOW);//Apaga el led verde
        lcd.setCursor(0,0);
        lcd.print(" Bomba Apagada  ");//La pantalla LCD indica que se apagó la bomba
        //lcd.print(humedad);
        //lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("               ");
      break;
      case 'A': //Significa que la bomba se ha encendido. Es decir se pulsó el boton de on (Encender bomba).
      digitalWrite(bomba, LOW);
      digitalWrite(ledRojo,LOW);//El led rojo y azul solo entran en funcionamiento cuando se activa el caso C,
      digitalWrite(ledAzul,LOW);//donde significa que se activo el modo automatico usando el sensor del suelo
      digitalWrite(ledVerde,HIGH);//Enciende el led verde
        lcd.setCursor(0,0);
        lcd.print(" Bomba Encendida ");//La pantalla LCD indica que se encendió la bomba
        //lcd.print(humedad);
        //lcd.print(" %");
        lcd.setCursor(0,1);
        lcd.print("               ");
      break;
      case 'C'://Activa el modo automatico, donde se hace uso del sensor de humedad del suelo
            Serial.print(humedad);Serial.println (" %");
        if(humedad < 20){//Si la humedad es menor a 20%
             Serial.println("Tierra seca, encendiendo bomba automatica");
            digitalWrite(bomba, LOW);//Enciende la bomba
            digitalWrite(ledRojo,HIGH);//Enciende el led rojo indicador de tierra seca
            digitalWrite(ledAzul,LOW);
            digitalWrite(ledVerde,HIGH);//Enciende el led verde
            lcd.setCursor(0,0);
            lcd.print("Tierra Seca: ");
            lcd.print(humedad);
            lcd.print(" %");
              //delay(1000);
            lcd.setCursor(0,1);
            lcd.print("Regando...     ");//La pantalla LCD indica que la bomba esta encendida,
                                        //Y ha comenzado a regar
          }
        if(humedad > 20){//Si la humedad es mayor a 20, significa que parte del sensor ya esta dentro del agua
            
            Serial.println("Tierra humeda, apagando bomba automaticamente");
             digitalWrite(bomba, HIGH);//Apaga la bomba
             digitalWrite(ledRojo,LOW);//Apaga el led rojo
            digitalWrite(ledAzul,HIGH);//Enciende el led azul indicador de tierra humeda
            digitalWrite(ledVerde,LOW);//Apaga el led verde
            lcd.setCursor(0,0);
            lcd.print("  Tierra Humeda  ");
              //lcd.print(humedad);
              //lcd.print(" %");
              //delay(1000);
            lcd.setCursor(0,1);
              //lcd.print(humedad);
            lcd.print("  Bomba Apagada ");//La pantalla LCD indica que la bomba se ha apagado
              //delay(1);
          }
        delay(1000);//Delay de un segundo para mostrar en el monitor serial
      break;
      case 'D'://Desactiva el modo automatico (Apaga la bomba)
      digitalWrite(bomba, HIGH);//Apaga la bomba
      //estado = Serial.read();
      digitalWrite(ledRojo,LOW);//Apaga todos los leds
      digitalWrite(ledAzul,LOW);//
      digitalWrite(ledVerde,LOW);//
      lcd.setCursor(0,0);
      lcd.print("  Bomba Apagada ");//La pantalla LCD indica que la bomba se ha apagado
      lcd.setCursor(0,1);
      //lcd.print(humedad);
      lcd.print("                    ");
      break;
      }
}

